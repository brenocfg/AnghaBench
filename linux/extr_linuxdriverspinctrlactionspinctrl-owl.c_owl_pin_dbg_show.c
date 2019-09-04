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
struct owl_pinctrl {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 struct owl_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void owl_pin_dbg_show(struct pinctrl_dev *pctrldev,
				struct seq_file *s,
				unsigned int offset)
{
	struct owl_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctrldev);

	seq_printf(s, "%s", dev_name(pctrl->dev));
}