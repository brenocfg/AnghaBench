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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct nfnetlink_subsystem {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  subsys; } ;

/* Variables and functions */
 size_t NFNL_SUBSYS_COUNT ; 
 size_t NFNL_SUBSYS_ID (int /*<<< orphan*/ ) ; 
 struct nfnetlink_subsystem const* rcu_dereference (int /*<<< orphan*/ ) ; 
 TYPE_1__* table ; 

__attribute__((used)) static inline const struct nfnetlink_subsystem *nfnetlink_get_subsys(u16 type)
{
	u8 subsys_id = NFNL_SUBSYS_ID(type);

	if (subsys_id >= NFNL_SUBSYS_COUNT)
		return NULL;

	return rcu_dereference(table[subsys_id].subsys);
}