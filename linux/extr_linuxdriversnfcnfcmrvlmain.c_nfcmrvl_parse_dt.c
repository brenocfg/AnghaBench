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
struct nfcmrvl_platform_data {int reset_n_io; int hci_muxed; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_is_valid (int) ; 
 scalar_t__ of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int of_get_named_gpio (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

int nfcmrvl_parse_dt(struct device_node *node,
		     struct nfcmrvl_platform_data *pdata)
{
	int reset_n_io;

	reset_n_io = of_get_named_gpio(node, "reset-n-io", 0);
	if (reset_n_io < 0) {
		pr_info("no reset-n-io config\n");
	} else if (!gpio_is_valid(reset_n_io)) {
		pr_err("invalid reset-n-io GPIO\n");
		return reset_n_io;
	}
	pdata->reset_n_io = reset_n_io;

	if (of_find_property(node, "hci-muxed", NULL))
		pdata->hci_muxed = 1;
	else
		pdata->hci_muxed = 0;

	return 0;
}