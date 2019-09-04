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
struct airo_info {TYPE_1__* dev; } ;
typedef  int /*<<< orphan*/  WepKeyRid ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int PC4500_writerid (struct airo_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  RID_WEP_PERM ; 
 int /*<<< orphan*/  RID_WEP_TEMP ; 
 int SUCCESS ; 
 int /*<<< orphan*/  airo_print_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int writeWepKeyRid(struct airo_info *ai, WepKeyRid *wkr, int perm, int lock)
{
	int rc;
	rc = PC4500_writerid(ai, RID_WEP_TEMP, wkr, sizeof(*wkr), lock);
	if (rc!=SUCCESS)
		airo_print_err(ai->dev->name, "WEP_TEMP set %x", rc);
	if (perm) {
		rc = PC4500_writerid(ai, RID_WEP_PERM, wkr, sizeof(*wkr), lock);
		if (rc!=SUCCESS)
			airo_print_err(ai->dev->name, "WEP_PERM set %x", rc);
	}
	return rc;
}