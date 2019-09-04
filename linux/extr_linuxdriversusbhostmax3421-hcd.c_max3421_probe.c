#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct usb_hcd {int /*<<< orphan*/  flags; } ;
struct device {struct max3421_hcd_platform_data* platform_data; scalar_t__ of_node; } ;
struct spi_device {int irq; struct device dev; } ;
struct max3421_hcd_platform_data {int vbus_active_level; int vbus_gpout; } ;
struct max3421_hcd {scalar_t__ spi_thread; void* rx; void* tx; int /*<<< orphan*/  ep_list; struct max3421_hcd* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_OF ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HCD_FLAG_POLL_RH ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IRQF_TRIGGER_LOW ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int MAX3421_GPOUT_COUNT ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  devm_kfree (struct device*,struct max3421_hcd_platform_data*) ; 
 struct max3421_hcd_platform_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct max3421_hcd* hcd_to_max3421 (struct usb_hcd*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ kthread_run (int /*<<< orphan*/ ,struct usb_hcd*,char*) ; 
 int /*<<< orphan*/  kthread_stop (scalar_t__) ; 
 int /*<<< orphan*/  max3421_hcd_desc ; 
 struct max3421_hcd* max3421_hcd_list ; 
 int /*<<< orphan*/  max3421_irq_handler ; 
 int max3421_of_vbus_en_pin (struct device*,struct max3421_hcd_platform_data*) ; 
 int /*<<< orphan*/  max3421_spi_thread ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct usb_hcd*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ spi_setup (struct spi_device*) ; 
 int usb_add_hcd (struct usb_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct usb_hcd* usb_create_hcd (int /*<<< orphan*/ *,struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int
max3421_probe(struct spi_device *spi)
{
	struct device *dev = &spi->dev;
	struct max3421_hcd *max3421_hcd;
	struct usb_hcd *hcd = NULL;
	struct max3421_hcd_platform_data *pdata = NULL;
	int retval = -ENOMEM;

	if (spi_setup(spi) < 0) {
		dev_err(&spi->dev, "Unable to setup SPI bus");
		return -EFAULT;
	}

	if (!spi->irq) {
		dev_err(dev, "Failed to get SPI IRQ");
		return -EFAULT;
	}

	if (IS_ENABLED(CONFIG_OF) && dev->of_node) {
		pdata = devm_kzalloc(&spi->dev, sizeof(*pdata), GFP_KERNEL);
		if (!pdata) {
			retval = -ENOMEM;
			goto error;
		}
		retval = max3421_of_vbus_en_pin(dev, pdata);
		if (retval)
			goto error;

		spi->dev.platform_data = pdata;
	}

	pdata = spi->dev.platform_data;
	if (!pdata) {
		dev_err(&spi->dev, "driver configuration data is not provided\n");
		retval = -EFAULT;
		goto error;
	}
	if (pdata->vbus_active_level > 1) {
		dev_err(&spi->dev, "vbus active level value %d is out of range (0/1)\n", pdata->vbus_active_level);
		retval = -EINVAL;
		goto error;
	}
	if (pdata->vbus_gpout < 1 || pdata->vbus_gpout > MAX3421_GPOUT_COUNT) {
		dev_err(&spi->dev, "vbus gpout value %d is out of range (1..8)\n", pdata->vbus_gpout);
		retval = -EINVAL;
		goto error;
	}

	hcd = usb_create_hcd(&max3421_hcd_desc, &spi->dev,
			     dev_name(&spi->dev));
	if (!hcd) {
		dev_err(&spi->dev, "failed to create HCD structure\n");
		goto error;
	}
	set_bit(HCD_FLAG_POLL_RH, &hcd->flags);
	max3421_hcd = hcd_to_max3421(hcd);
	max3421_hcd->next = max3421_hcd_list;
	max3421_hcd_list = max3421_hcd;
	INIT_LIST_HEAD(&max3421_hcd->ep_list);

	max3421_hcd->tx = kmalloc(sizeof(*max3421_hcd->tx), GFP_KERNEL);
	if (!max3421_hcd->tx)
		goto error;
	max3421_hcd->rx = kmalloc(sizeof(*max3421_hcd->rx), GFP_KERNEL);
	if (!max3421_hcd->rx)
		goto error;

	max3421_hcd->spi_thread = kthread_run(max3421_spi_thread, hcd,
					      "max3421_spi_thread");
	if (max3421_hcd->spi_thread == ERR_PTR(-ENOMEM)) {
		dev_err(&spi->dev,
			"failed to create SPI thread (out of memory)\n");
		goto error;
	}

	retval = usb_add_hcd(hcd, 0, 0);
	if (retval) {
		dev_err(&spi->dev, "failed to add HCD\n");
		goto error;
	}

	retval = request_irq(spi->irq, max3421_irq_handler,
			     IRQF_TRIGGER_LOW, "max3421", hcd);
	if (retval < 0) {
		dev_err(&spi->dev, "failed to request irq %d\n", spi->irq);
		goto error;
	}
	return 0;

error:
	if (IS_ENABLED(CONFIG_OF) && dev->of_node && pdata) {
		devm_kfree(&spi->dev, pdata);
		spi->dev.platform_data = NULL;
	}

	if (hcd) {
		kfree(max3421_hcd->tx);
		kfree(max3421_hcd->rx);
		if (max3421_hcd->spi_thread)
			kthread_stop(max3421_hcd->spi_thread);
		usb_put_hcd(hcd);
	}
	return retval;
}