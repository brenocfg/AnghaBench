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
typedef  void* u32 ;
struct mtu3 {int is_u3_ip; int /*<<< orphan*/  dev; void* hw_version; int /*<<< orphan*/  ippc_base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SSUSB_IP_DEV_U3_PORT_NUM (void*) ; 
 int /*<<< orphan*/  U3D_SSUSB_HW_ID ; 
 int /*<<< orphan*/  U3D_SSUSB_IP_DEV_CAP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,void*,char*) ; 
 int mtu3_device_enable (struct mtu3*) ; 
 int /*<<< orphan*/  mtu3_device_reset (struct mtu3*) ; 
 int mtu3_mem_alloc (struct mtu3*) ; 
 void* mtu3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtu3_regs_init (struct mtu3*) ; 

__attribute__((used)) static int mtu3_hw_init(struct mtu3 *mtu)
{
	u32 cap_dev;
	int ret;

	mtu->hw_version = mtu3_readl(mtu->ippc_base, U3D_SSUSB_HW_ID);

	cap_dev = mtu3_readl(mtu->ippc_base, U3D_SSUSB_IP_DEV_CAP);
	mtu->is_u3_ip = !!SSUSB_IP_DEV_U3_PORT_NUM(cap_dev);

	dev_info(mtu->dev, "IP version 0x%x(%s IP)\n", mtu->hw_version,
		mtu->is_u3_ip ? "U3" : "U2");

	mtu3_device_reset(mtu);

	ret = mtu3_device_enable(mtu);
	if (ret) {
		dev_err(mtu->dev, "device enable failed %d\n", ret);
		return ret;
	}

	ret = mtu3_mem_alloc(mtu);
	if (ret)
		return -ENOMEM;

	mtu3_regs_init(mtu);

	return 0;
}