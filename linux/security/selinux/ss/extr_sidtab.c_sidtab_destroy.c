#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct sidtab {TYPE_2__* roots; TYPE_1__* isids; } ;
struct TYPE_4__ {int /*<<< orphan*/  ptr_inner; } ;
struct TYPE_3__ {int /*<<< orphan*/  context; scalar_t__ set; } ;

/* Variables and functions */
 size_t SECINITSID_NUM ; 
 size_t SIDTAB_MAX_LEVEL ; 
 int /*<<< orphan*/  context_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sidtab_destroy_tree (TYPE_2__,size_t) ; 

void sidtab_destroy(struct sidtab *s)
{
	u32 i, level;

	for (i = 0; i < SECINITSID_NUM; i++)
		if (s->isids[i].set)
			context_destroy(&s->isids[i].context);

	level = SIDTAB_MAX_LEVEL;
	while (level && !s->roots[level].ptr_inner)
		--level;

	sidtab_destroy_tree(s->roots[level], level);
}