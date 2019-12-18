#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ len; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ ltree_level ;
struct TYPE_10__ {int numlevel; } ;
typedef  TYPE_2__ ltree ;

/* Variables and functions */
 TYPE_1__* LEVEL_NEXT (TYPE_1__*) ; 
 TYPE_1__* LTREE_FIRST (TYPE_2__ const*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

bool
inner_isparent(const ltree *c, const ltree *p)
{
	ltree_level *cl = LTREE_FIRST(c);
	ltree_level *pl = LTREE_FIRST(p);
	int			pn = p->numlevel;

	if (pn > c->numlevel)
		return false;

	while (pn > 0)
	{
		if (cl->len != pl->len)
			return false;
		if (memcmp(cl->name, pl->name, cl->len) != 0)
			return false;

		pn--;
		cl = LEVEL_NEXT(cl);
		pl = LEVEL_NEXT(pl);
	}
	return true;
}