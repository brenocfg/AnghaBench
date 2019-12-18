#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_7__ {int /*<<< orphan*/  data; struct TYPE_7__* next; } ;
typedef  TYPE_2__ spl_ptr_llist_element ;
struct TYPE_9__ {int /*<<< orphan*/  properties; } ;
struct TYPE_8__ {int /*<<< orphan*/  flags; TYPE_5__ std; TYPE_1__* llist; } ;
typedef  TYPE_3__ spl_dllist_object ;
typedef  int /*<<< orphan*/  copy_ctor_func_t ;
struct TYPE_6__ {TYPE_2__* head; } ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_ADDREF (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_REFCOUNTED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_index_zval (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rebuild_object_properties (TYPE_5__*) ; 
 int /*<<< orphan*/  spl_ce_SplDoublyLinkedList ; 
 TYPE_3__* spl_dllist_from_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * spl_gen_private_prop_name (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  zend_hash_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_new_array (int) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ zval_add_ref ; 

__attribute__((used)) static HashTable* spl_dllist_object_get_debug_info(zend_object *obj, int *is_temp) /* {{{{ */
{
	spl_dllist_object     *intern  = spl_dllist_from_obj(obj);
	spl_ptr_llist_element *current = intern->llist->head, *next;
	zval tmp, dllist_array;
	zend_string *pnstr;
	int  i = 0;
	HashTable *debug_info;
	*is_temp = 1;

	if (!intern->std.properties) {
		rebuild_object_properties(&intern->std);
	}

	debug_info = zend_new_array(1);
	zend_hash_copy(debug_info, intern->std.properties, (copy_ctor_func_t) zval_add_ref);

	pnstr = spl_gen_private_prop_name(spl_ce_SplDoublyLinkedList, "flags", sizeof("flags")-1);
	ZVAL_LONG(&tmp, intern->flags);
	zend_hash_add(debug_info, pnstr, &tmp);
	zend_string_release_ex(pnstr, 0);

	array_init(&dllist_array);

	while (current) {
		next = current->next;

		add_index_zval(&dllist_array, i, &current->data);
		if (Z_REFCOUNTED(current->data)) {
			Z_ADDREF(current->data);
		}
		i++;

		current = next;
	}

	pnstr = spl_gen_private_prop_name(spl_ce_SplDoublyLinkedList, "dllist", sizeof("dllist")-1);
	zend_hash_add(debug_info, pnstr, &dllist_array);
	zend_string_release_ex(pnstr, 0);

	return debug_info;
}