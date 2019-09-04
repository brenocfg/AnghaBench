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
struct tipc_member {scalar_t__ state; } ;
struct tipc_group {int /*<<< orphan*/  active_cnt; } ;

/* Variables and functions */
 scalar_t__ MBR_ACTIVE ; 
 scalar_t__ MBR_RECLAIMING ; 
 scalar_t__ MBR_REMITTED ; 

__attribute__((used)) static void tipc_group_decr_active(struct tipc_group *grp,
				   struct tipc_member *m)
{
	if (m->state == MBR_ACTIVE || m->state == MBR_RECLAIMING ||
	    m->state == MBR_REMITTED)
		grp->active_cnt--;
}