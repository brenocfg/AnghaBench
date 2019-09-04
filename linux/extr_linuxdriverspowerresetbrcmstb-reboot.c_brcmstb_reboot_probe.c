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
struct TYPE_2__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct of_device_id {int /*<<< orphan*/  data; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RESET_SOURCE_ENABLE_REG ; 
 int /*<<< orphan*/  SW_MASTER_RESET_REG ; 
 int /*<<< orphan*/  brcmstb_restart_nb ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  of_match ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,struct device_node*) ; 
 int of_property_read_u32_index (struct device_node*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int register_restart_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap ; 
 int /*<<< orphan*/  reset_masks ; 
 int /*<<< orphan*/  rst_src_en ; 
 int /*<<< orphan*/  sw_mstr_rst ; 
 int /*<<< orphan*/  syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 

__attribute__((used)) static int brcmstb_reboot_probe(struct platform_device *pdev)
{
	int rc;
	struct device_node *np = pdev->dev.of_node;
	const struct of_device_id *of_id;

	of_id = of_match_node(of_match, np);
	if (!of_id) {
		pr_err("failed to look up compatible string\n");
		return -EINVAL;
	}
	reset_masks = of_id->data;

	regmap = syscon_regmap_lookup_by_phandle(np, "syscon");
	if (IS_ERR(regmap)) {
		pr_err("failed to get syscon phandle\n");
		return -EINVAL;
	}

	rc = of_property_read_u32_index(np, "syscon", RESET_SOURCE_ENABLE_REG,
					&rst_src_en);
	if (rc) {
		pr_err("can't get rst_src_en offset (%d)\n", rc);
		return -EINVAL;
	}

	rc = of_property_read_u32_index(np, "syscon", SW_MASTER_RESET_REG,
					&sw_mstr_rst);
	if (rc) {
		pr_err("can't get sw_mstr_rst offset (%d)\n", rc);
		return -EINVAL;
	}

	rc = register_restart_handler(&brcmstb_restart_nb);
	if (rc)
		dev_err(&pdev->dev,
			"cannot register restart handler (err=%d)\n", rc);

	return rc;
}