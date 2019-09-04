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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ data; } ;
struct nfs4_deviceid_node {TYPE_1__ deviceid; } ;

/* Variables and functions */
 scalar_t__ nfs4_test_deviceid_unavailable (struct nfs4_deviceid_node*) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
ff_layout_test_devid_unavailable(struct nfs4_deviceid_node *node)
{
	/*
	 * Flexfiles should never mark a DS unavailable, but if it does
	 * print a (ratelimited) warning as this can affect performance.
	 */
	if (nfs4_test_deviceid_unavailable(node)) {
		u32 *p = (u32 *)node->deviceid.data;

		pr_warn_ratelimited("NFS: flexfiles layout referencing an "
				"unavailable device [%x%x%x%x]\n",
				p[0], p[1], p[2], p[3]);
		return true;
	}
	return false;
}