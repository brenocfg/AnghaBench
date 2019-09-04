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
struct mtu3 {int /*<<< orphan*/  dev; int /*<<< orphan*/  mac_base; } ;

/* Variables and functions */
 int SOFT_CONN ; 
 int SUSPENDM_ENABLE ; 
 int /*<<< orphan*/  U3D_POWER_MANAGEMENT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mtu3_clrbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtu3_setbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void mtu3_hs_softconn_set(struct mtu3 *mtu, bool enable)
{
	if (enable) {
		mtu3_setbits(mtu->mac_base, U3D_POWER_MANAGEMENT,
			SOFT_CONN | SUSPENDM_ENABLE);
	} else {
		mtu3_clrbits(mtu->mac_base, U3D_POWER_MANAGEMENT,
			SOFT_CONN | SUSPENDM_ENABLE);
	}
	dev_dbg(mtu->dev, "SOFTCONN = %d\n", !!enable);
}