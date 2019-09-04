#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wlcore_platdev_data {int /*<<< orphan*/  if_ops; TYPE_1__* family; } ;
struct wl1271 {scalar_t__ num_tx_desc; int irq_flags; int initialized; int /*<<< orphan*/  nvs_loading_complete; int /*<<< orphan*/ * nvs; int /*<<< orphan*/  irq; TYPE_2__* ops; int /*<<< orphan*/  if_ops; scalar_t__ nvs_len; struct platform_device* pdev; } ;
struct resource {int flags; int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;
struct firmware {scalar_t__ size; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/ * irq_handler_t ;
struct TYPE_4__ {int (* setup ) (struct wl1271*) ;int (* identify_chip ) (struct wl1271*) ;} ;
struct TYPE_3__ {scalar_t__ nvs_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DEBUG_BOOT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_MASK ; 
 int IRQF_TRIGGER_RISING ; 
 scalar_t__ WLCORE_MAX_TX_DESCRIPTORS ; 
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 struct wlcore_platdev_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct wl1271*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmemdup (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct wl1271*) ; 
 int stub1 (struct wl1271*) ; 
 int stub2 (struct wl1271*) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  wl1271_error (char*) ; 
 int wl1271_init_ieee80211 (struct wl1271*) ; 
 int /*<<< orphan*/  wl1271_power_off (struct wl1271*) ; 
 int wl1271_register_hw (struct wl1271*) ; 
 int /*<<< orphan*/  wl1271_unregister_hw (struct wl1271*) ; 
 int wl12xx_get_hw_info (struct wl1271*) ; 
 int wl12xx_set_power_on (struct wl1271*) ; 
 int /*<<< orphan*/  wlcore_adjust_conf (struct wl1271*) ; 
 int /*<<< orphan*/ * wlcore_hardirq ; 
 int /*<<< orphan*/  wlcore_irq ; 
 int wlcore_sysfs_init (struct wl1271*) ; 

__attribute__((used)) static void wlcore_nvs_cb(const struct firmware *fw, void *context)
{
	struct wl1271 *wl = context;
	struct platform_device *pdev = wl->pdev;
	struct wlcore_platdev_data *pdev_data = dev_get_platdata(&pdev->dev);
	struct resource *res;

	int ret;
	irq_handler_t hardirq_fn = NULL;

	if (fw) {
		wl->nvs = kmemdup(fw->data, fw->size, GFP_KERNEL);
		if (!wl->nvs) {
			wl1271_error("Could not allocate nvs data");
			goto out;
		}
		wl->nvs_len = fw->size;
	} else if (pdev_data->family->nvs_name) {
		wl1271_debug(DEBUG_BOOT, "Could not get nvs file %s",
			     pdev_data->family->nvs_name);
		wl->nvs = NULL;
		wl->nvs_len = 0;
	} else {
		wl->nvs = NULL;
		wl->nvs_len = 0;
	}

	ret = wl->ops->setup(wl);
	if (ret < 0)
		goto out_free_nvs;

	BUG_ON(wl->num_tx_desc > WLCORE_MAX_TX_DESCRIPTORS);

	/* adjust some runtime configuration parameters */
	wlcore_adjust_conf(wl);

	res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (!res) {
		wl1271_error("Could not get IRQ resource");
		goto out_free_nvs;
	}

	wl->irq = res->start;
	wl->irq_flags = res->flags & IRQF_TRIGGER_MASK;
	wl->if_ops = pdev_data->if_ops;

	if (wl->irq_flags & (IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING))
		hardirq_fn = wlcore_hardirq;
	else
		wl->irq_flags |= IRQF_ONESHOT;

	ret = wl12xx_set_power_on(wl);
	if (ret < 0)
		goto out_free_nvs;

	ret = wl12xx_get_hw_info(wl);
	if (ret < 0) {
		wl1271_error("couldn't get hw info");
		wl1271_power_off(wl);
		goto out_free_nvs;
	}

	ret = request_threaded_irq(wl->irq, hardirq_fn, wlcore_irq,
				   wl->irq_flags, pdev->name, wl);
	if (ret < 0) {
		wl1271_error("interrupt configuration failed");
		wl1271_power_off(wl);
		goto out_free_nvs;
	}

#ifdef CONFIG_PM
	ret = enable_irq_wake(wl->irq);
	if (!ret) {
		wl->irq_wake_enabled = true;
		device_init_wakeup(wl->dev, 1);
		if (pdev_data->pwr_in_suspend)
			wl->hw->wiphy->wowlan = &wlcore_wowlan_support;
	}
#endif
	disable_irq(wl->irq);
	wl1271_power_off(wl);

	ret = wl->ops->identify_chip(wl);
	if (ret < 0)
		goto out_irq;

	ret = wl1271_init_ieee80211(wl);
	if (ret)
		goto out_irq;

	ret = wl1271_register_hw(wl);
	if (ret)
		goto out_irq;

	ret = wlcore_sysfs_init(wl);
	if (ret)
		goto out_unreg;

	wl->initialized = true;
	goto out;

out_unreg:
	wl1271_unregister_hw(wl);

out_irq:
	free_irq(wl->irq, wl);

out_free_nvs:
	kfree(wl->nvs);

out:
	release_firmware(fw);
	complete_all(&wl->nvs_loading_complete);
}