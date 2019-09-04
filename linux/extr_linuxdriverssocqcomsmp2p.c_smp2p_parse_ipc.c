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
struct qcom_smp2p {int /*<<< orphan*/  ipc_bit; int /*<<< orphan*/  ipc_offset; int /*<<< orphan*/  ipc_regmap; struct device* dev; } ;
struct device_node {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int of_property_read_u32_index (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  syscon_node_to_regmap (struct device_node*) ; 

__attribute__((used)) static int smp2p_parse_ipc(struct qcom_smp2p *smp2p)
{
	struct device_node *syscon;
	struct device *dev = smp2p->dev;
	const char *key;
	int ret;

	syscon = of_parse_phandle(dev->of_node, "qcom,ipc", 0);
	if (!syscon) {
		dev_err(dev, "no qcom,ipc node\n");
		return -ENODEV;
	}

	smp2p->ipc_regmap = syscon_node_to_regmap(syscon);
	if (IS_ERR(smp2p->ipc_regmap))
		return PTR_ERR(smp2p->ipc_regmap);

	key = "qcom,ipc";
	ret = of_property_read_u32_index(dev->of_node, key, 1, &smp2p->ipc_offset);
	if (ret < 0) {
		dev_err(dev, "no offset in %s\n", key);
		return -EINVAL;
	}

	ret = of_property_read_u32_index(dev->of_node, key, 2, &smp2p->ipc_bit);
	if (ret < 0) {
		dev_err(dev, "no bit in %s\n", key);
		return -EINVAL;
	}

	return 0;
}