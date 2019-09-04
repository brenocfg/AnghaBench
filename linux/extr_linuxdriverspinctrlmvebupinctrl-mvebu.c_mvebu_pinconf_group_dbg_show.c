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
struct seq_file {int dummy; } ;
struct pinctrl_dev {int dummy; } ;
struct mvebu_pinctrl_group {int num_settings; struct mvebu_mpp_ctrl_setting* settings; } ;
struct mvebu_pinctrl {int variant; struct mvebu_pinctrl_group* groups; } ;
struct mvebu_mpp_ctrl_setting {int flags; int variant; scalar_t__ subname; scalar_t__ name; } ;

/* Variables and functions */
 int MVEBU_SETTING_GPI ; 
 int MVEBU_SETTING_GPO ; 
 scalar_t__ mvebu_pinconf_group_get (struct pinctrl_dev*,unsigned int,unsigned long*) ; 
 struct mvebu_mpp_ctrl_setting* mvebu_pinctrl_find_setting_by_val (struct mvebu_pinctrl*,struct mvebu_pinctrl_group*,unsigned long) ; 
 struct mvebu_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,scalar_t__) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void mvebu_pinconf_group_dbg_show(struct pinctrl_dev *pctldev,
					struct seq_file *s, unsigned gid)
{
	struct mvebu_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	struct mvebu_pinctrl_group *grp = &pctl->groups[gid];
	struct mvebu_mpp_ctrl_setting *curr;
	unsigned long config;
	unsigned n;

	if (mvebu_pinconf_group_get(pctldev, gid, &config))
		return;

	curr = mvebu_pinctrl_find_setting_by_val(pctl, grp, config);

	if (curr) {
		seq_printf(s, "current: %s", curr->name);
		if (curr->subname)
			seq_printf(s, "(%s)", curr->subname);
		if (curr->flags & (MVEBU_SETTING_GPO | MVEBU_SETTING_GPI)) {
			seq_putc(s, '(');
			if (curr->flags & MVEBU_SETTING_GPI)
				seq_putc(s, 'i');
			if (curr->flags & MVEBU_SETTING_GPO)
				seq_putc(s, 'o');
			seq_putc(s, ')');
		}
	} else {
		seq_puts(s, "current: UNKNOWN");
	}

	if (grp->num_settings > 1) {
		seq_puts(s, ", available = [");
		for (n = 0; n < grp->num_settings; n++) {
			if (curr == &grp->settings[n])
				continue;

			/* skip unsupported settings for this variant */
			if (pctl->variant &&
			    !(pctl->variant & grp->settings[n].variant))
				continue;

			seq_printf(s, " %s", grp->settings[n].name);
			if (grp->settings[n].subname)
				seq_printf(s, "(%s)", grp->settings[n].subname);
			if (grp->settings[n].flags &
				(MVEBU_SETTING_GPO | MVEBU_SETTING_GPI)) {
				seq_putc(s, '(');
				if (grp->settings[n].flags & MVEBU_SETTING_GPI)
					seq_putc(s, 'i');
				if (grp->settings[n].flags & MVEBU_SETTING_GPO)
					seq_putc(s, 'o');
				seq_putc(s, ')');
			}
		}
		seq_puts(s, " ]");
	}
}