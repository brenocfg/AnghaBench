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
typedef  int /*<<< orphan*/  u16 ;
struct tipc_group {int /*<<< orphan*/  bc_snd_nxt; } ;

/* Variables and functions */

u16 tipc_group_bc_snd_nxt(struct tipc_group *grp)
{
	return grp->bc_snd_nxt;
}