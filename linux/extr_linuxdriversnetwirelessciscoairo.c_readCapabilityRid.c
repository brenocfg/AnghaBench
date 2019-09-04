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
struct airo_info {int dummy; } ;
typedef  int /*<<< orphan*/  CapabilityRid ;

/* Variables and functions */
 int PC4500_readrid (struct airo_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  RID_CAPABILITIES ; 

__attribute__((used)) static int readCapabilityRid(struct airo_info *ai, CapabilityRid *capr, int lock)
{
	return PC4500_readrid(ai, RID_CAPABILITIES, capr, sizeof(*capr), lock);
}