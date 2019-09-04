#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct msm_pinctrl {int /*<<< orphan*/  dev; TYPE_1__* soc; } ;
struct gpio_chip {int /*<<< orphan*/  valid_mask; } ;
struct TYPE_2__ {unsigned int ngpios; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int device_property_read_u16_array (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int msm_gpio_init_valid_mask(struct gpio_chip *chip,
				    struct msm_pinctrl *pctrl)
{
	int ret;
	unsigned int len, i;
	unsigned int max_gpios = pctrl->soc->ngpios;
	u16 *tmp;

	/* The number of GPIOs in the ACPI tables */
	len = ret = device_property_read_u16_array(pctrl->dev, "gpios", NULL, 0);
	if (ret < 0)
		return 0;

	if (ret > max_gpios)
		return -EINVAL;

	tmp = kmalloc_array(len, sizeof(*tmp), GFP_KERNEL);
	if (!tmp)
		return -ENOMEM;

	ret = device_property_read_u16_array(pctrl->dev, "gpios", tmp, len);
	if (ret < 0) {
		dev_err(pctrl->dev, "could not read list of GPIOs\n");
		goto out;
	}

	bitmap_zero(chip->valid_mask, max_gpios);
	for (i = 0; i < len; i++)
		set_bit(tmp[i], chip->valid_mask);

out:
	kfree(tmp);
	return ret;
}