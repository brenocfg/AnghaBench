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
typedef  int u16 ;
struct tipc_mon_domain {int /*<<< orphan*/  members; } ;

/* Variables and functions */

__attribute__((used)) static int dom_rec_len(struct tipc_mon_domain *dom, u16 mcnt)
{
	return ((void *)&dom->members - (void *)dom) + (mcnt * sizeof(u32));
}