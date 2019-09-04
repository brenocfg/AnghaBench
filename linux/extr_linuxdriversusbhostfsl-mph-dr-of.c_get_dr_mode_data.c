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
struct fsl_usb2_dev_data {int /*<<< orphan*/  dr_mode; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct fsl_usb2_dev_data*) ; 
 struct fsl_usb2_dev_data* dr_mode_data ; 
 unsigned char* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,struct device_node*) ; 
 int /*<<< orphan*/  strcmp (unsigned char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct fsl_usb2_dev_data *get_dr_mode_data(struct device_node *np)
{
	const unsigned char *prop;
	int i;

	prop = of_get_property(np, "dr_mode", NULL);
	if (prop) {
		for (i = 0; i < ARRAY_SIZE(dr_mode_data); i++) {
			if (!strcmp(prop, dr_mode_data[i].dr_mode))
				return &dr_mode_data[i];
		}
	}
	pr_warn("%pOF: Invalid 'dr_mode' property, fallback to host mode\n",
		np);
	return &dr_mode_data[0]; /* mode not specified, use host */
}