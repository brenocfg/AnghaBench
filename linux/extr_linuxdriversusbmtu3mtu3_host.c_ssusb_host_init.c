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
struct ssusb_mtk {struct device* dev; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,struct device_node*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int of_platform_populate (struct device_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  ssusb_host_setup (struct ssusb_mtk*) ; 

int ssusb_host_init(struct ssusb_mtk *ssusb, struct device_node *parent_dn)
{
	struct device *parent_dev = ssusb->dev;
	int ret;

	ssusb_host_setup(ssusb);

	ret = of_platform_populate(parent_dn, NULL, NULL, parent_dev);
	if (ret) {
		dev_dbg(parent_dev, "failed to create child devices at %pOF\n",
				parent_dn);
		return ret;
	}

	dev_info(parent_dev, "xHCI platform device register success...\n");

	return 0;
}