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
struct tipc_group {int member_cnt; int max_active; } ;

/* Variables and functions */
 int ADV_ACTIVE ; 
 int ADV_IDLE ; 
 int FLOWCTL_BLK_SZ ; 
 int max (int,int) ; 
 int min (int,int) ; 

__attribute__((used)) static int tipc_group_rcvbuf_limit(struct tipc_group *grp)
{
	int max_active, active_pool, idle_pool;
	int mcnt = grp->member_cnt + 1;

	/* Limit simultaneous reception from other members */
	max_active = min(mcnt / 8, 64);
	max_active = max(max_active, 16);
	grp->max_active = max_active;

	/* Reserve blocks for active and idle members */
	active_pool = max_active * ADV_ACTIVE;
	idle_pool = (mcnt - max_active) * ADV_IDLE;

	/* Scale to bytes, considering worst-case truesize/msgsize ratio */
	return (active_pool + idle_pool) * FLOWCTL_BLK_SZ * 4;
}