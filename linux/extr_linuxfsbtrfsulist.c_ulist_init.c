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
struct ulist {scalar_t__ nnodes; int /*<<< orphan*/  root; int /*<<< orphan*/  nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_ROOT ; 

void ulist_init(struct ulist *ulist)
{
	INIT_LIST_HEAD(&ulist->nodes);
	ulist->root = RB_ROOT;
	ulist->nnodes = 0;
}