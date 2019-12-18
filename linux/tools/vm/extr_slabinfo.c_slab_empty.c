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
struct slabinfo {scalar_t__ objects; scalar_t__ slabs; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_obj (struct slabinfo*,char*,int) ; 

__attribute__((used)) static int slab_empty(struct slabinfo *s)
{
	if (s->objects > 0)
		return 0;

	/*
	 * We may still have slabs even if there are no objects. Shrinking will
	 * remove them.
	 */
	if (s->slabs != 0)
		set_obj(s, "shrink", 1);

	return 1;
}