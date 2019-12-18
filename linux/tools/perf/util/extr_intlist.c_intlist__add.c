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
struct intlist {int /*<<< orphan*/  rblist; } ;

/* Variables and functions */
 int rblist__add_node (int /*<<< orphan*/ *,void*) ; 

int intlist__add(struct intlist *ilist, int i)
{
	return rblist__add_node(&ilist->rblist, (void *)((long)i));
}