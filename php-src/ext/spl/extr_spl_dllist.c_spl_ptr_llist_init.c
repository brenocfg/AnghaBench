#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  spl_ptr_llist_dtor_func ;
typedef  int /*<<< orphan*/  spl_ptr_llist_ctor_func ;
struct TYPE_4__ {int /*<<< orphan*/  ctor; int /*<<< orphan*/  dtor; scalar_t__ count; int /*<<< orphan*/ * tail; int /*<<< orphan*/ * head; } ;
typedef  TYPE_1__ spl_ptr_llist ;

/* Variables and functions */
 TYPE_1__* emalloc (int) ; 

__attribute__((used)) static spl_ptr_llist *spl_ptr_llist_init(spl_ptr_llist_ctor_func ctor, spl_ptr_llist_dtor_func dtor) /* {{{ */
{
	spl_ptr_llist *llist = emalloc(sizeof(spl_ptr_llist));

	llist->head  = NULL;
	llist->tail  = NULL;
	llist->count = 0;
	llist->dtor  = dtor;
	llist->ctor  = ctor;

	return llist;
}