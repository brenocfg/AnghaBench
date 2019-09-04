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
struct pinctrl_dev {int dummy; } ;
struct imx1_pinctrl {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  MX1_PUEN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx1_write_bit (struct imx1_pinctrl*,unsigned int,unsigned long,int /*<<< orphan*/ ) ; 
 TYPE_1__* pin_desc_get (struct pinctrl_dev*,unsigned int) ; 
 struct imx1_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int imx1_pinconf_set(struct pinctrl_dev *pctldev,
			     unsigned pin_id, unsigned long *configs,
			     unsigned num_configs)
{
	struct imx1_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);
	int i;

	for (i = 0; i != num_configs; ++i) {
		imx1_write_bit(ipctl, pin_id, configs[i] & 0x01, MX1_PUEN);

		dev_dbg(ipctl->dev, "pinconf set pullup pin %s\n",
			pin_desc_get(pctldev, pin_id)->name);
	}

	return 0;
}