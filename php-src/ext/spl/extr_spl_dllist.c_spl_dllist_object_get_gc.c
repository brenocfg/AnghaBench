#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_6__ {struct TYPE_6__* next; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ spl_ptr_llist_element ;
struct TYPE_7__ {scalar_t__ gc_data_count; int /*<<< orphan*/ * gc_data; TYPE_1__* llist; } ;
typedef  TYPE_3__ spl_dllist_object ;
struct TYPE_5__ {scalar_t__ count; TYPE_2__* head; } ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  ZVAL_COPY_VALUE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * safe_erealloc (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ ) ; 
 TYPE_3__* spl_dllist_from_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_std_get_properties (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HashTable *spl_dllist_object_get_gc(zend_object *obj, zval **gc_data, int *gc_data_count) /* {{{ */
{
	spl_dllist_object *intern = spl_dllist_from_obj(obj);
	spl_ptr_llist_element *current = intern->llist->head;
	int i = 0;

	if (intern->gc_data_count < intern->llist->count) {
		intern->gc_data_count = intern->llist->count;
		intern->gc_data = safe_erealloc(intern->gc_data, intern->gc_data_count, sizeof(zval), 0);
	}

	while (current) {
		ZVAL_COPY_VALUE(&intern->gc_data[i++], &current->data);
		current = current->next;
	}

	*gc_data = intern->gc_data;
	*gc_data_count = i;
	return zend_std_get_properties(obj);
}