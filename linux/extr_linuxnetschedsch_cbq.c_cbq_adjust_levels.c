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
struct cbq_class {int level; struct cbq_class* children; struct cbq_class* sibling; struct cbq_class* tparent; } ;

/* Variables and functions */

__attribute__((used)) static void cbq_adjust_levels(struct cbq_class *this)
{
	if (this == NULL)
		return;

	do {
		int level = 0;
		struct cbq_class *cl;

		cl = this->children;
		if (cl) {
			do {
				if (cl->level > level)
					level = cl->level;
			} while ((cl = cl->sibling) != this->children);
		}
		this->level = level + 1;
	} while ((this = this->tparent) != NULL);
}