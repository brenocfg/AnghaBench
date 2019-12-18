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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct neighbour {int dummy; } ;

/* Variables and functions */
 int __neigh_update (struct neighbour*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int neigh_update(struct neighbour *neigh, const u8 *lladdr, u8 new,
		 u32 flags, u32 nlmsg_pid)
{
	return __neigh_update(neigh, lladdr, new, flags, nlmsg_pid, NULL);
}