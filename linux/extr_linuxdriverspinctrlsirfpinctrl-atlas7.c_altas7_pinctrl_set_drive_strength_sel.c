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
typedef  size_t u32 ;
struct pinctrl_dev {int dummy; } ;
struct atlas7_pmx {TYPE_1__* pctl_data; } ;
struct atlas7_pad_config {size_t type; } ;
struct TYPE_2__ {struct atlas7_pad_config* confs; } ;

/* Variables and functions */
 size_t DS_NULL ; 
 int ENOTSUPP ; 
 int __altas7_pinctrl_set_drive_strength_sel (struct pinctrl_dev*,size_t,size_t) ; 
 size_t convert_current_to_drive_strength (size_t,size_t) ; 
 struct atlas7_pmx* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  pr_debug (char*,size_t,size_t,size_t,char*) ; 
 int /*<<< orphan*/  pr_err (char*,size_t,size_t,size_t) ; 

__attribute__((used)) static int altas7_pinctrl_set_drive_strength_sel(struct pinctrl_dev *pctldev,
						u32 pin, u32 ma)
{
	struct atlas7_pmx *pmx = pinctrl_dev_get_drvdata(pctldev);
	struct atlas7_pad_config *conf = &pmx->pctl_data->confs[pin];
	u32 type = conf->type;
	u32 sel;
	int ret;

	sel = convert_current_to_drive_strength(conf->type, ma);
	if (DS_NULL == sel) {
		pr_err("Pad#%d type[%d] doesn't support ds current[%d]!\n",
		pin, type, ma);
		return -ENOTSUPP;
	}

	ret =  __altas7_pinctrl_set_drive_strength_sel(pctldev,
						pin, sel);
	pr_debug("PIN_CFG ### SET PIN#%d DS:%d MA:%d == %s ####\n",
		pin, sel, ma, ret?"FAILED":"OK");
	return ret;
}