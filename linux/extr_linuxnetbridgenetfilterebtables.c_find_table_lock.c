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
struct TYPE_2__ {int /*<<< orphan*/ * tables; } ;
struct net {TYPE_1__ xt; } ;
struct mutex {int dummy; } ;
struct ebt_table {int dummy; } ;

/* Variables and functions */
 size_t NFPROTO_BRIDGE ; 
 struct ebt_table* find_inlist_lock (int /*<<< orphan*/ *,char const*,char*,int*,struct mutex*) ; 

__attribute__((used)) static inline struct ebt_table *
find_table_lock(struct net *net, const char *name, int *error,
		struct mutex *mutex)
{
	return find_inlist_lock(&net->xt.tables[NFPROTO_BRIDGE], name,
				"ebtable_", error, mutex);
}