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
struct tep_handle {TYPE_1__* func_resolver; } ;
struct func_map {unsigned long long addr; int /*<<< orphan*/ * func; int /*<<< orphan*/ * mod; } ;
struct TYPE_2__ {int /*<<< orphan*/  priv; int /*<<< orphan*/ * (* func ) (int /*<<< orphan*/ ,unsigned long long*,int /*<<< orphan*/ **) ;struct func_map map; } ;

/* Variables and functions */
 struct func_map* __find_func (struct tep_handle*,unsigned long long) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,unsigned long long*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static struct func_map *
find_func(struct tep_handle *tep, unsigned long long addr)
{
	struct func_map *map;

	if (!tep->func_resolver)
		return __find_func(tep, addr);

	map = &tep->func_resolver->map;
	map->mod  = NULL;
	map->addr = addr;
	map->func = tep->func_resolver->func(tep->func_resolver->priv,
					     &map->addr, &map->mod);
	if (map->func == NULL)
		return NULL;

	return map;
}