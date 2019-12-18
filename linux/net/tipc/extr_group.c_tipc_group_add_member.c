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
typedef  int /*<<< orphan*/  u32 ;
struct tipc_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MBR_PUBLISHED ; 
 int /*<<< orphan*/  tipc_group_create_member (struct tipc_group*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void tipc_group_add_member(struct tipc_group *grp, u32 node,
			   u32 port, u32 instance)
{
	tipc_group_create_member(grp, node, port, instance, MBR_PUBLISHED);
}