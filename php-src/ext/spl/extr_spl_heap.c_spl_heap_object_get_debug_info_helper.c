#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  zend_object ;
typedef  int /*<<< orphan*/  zend_class_entry ;
typedef  int /*<<< orphan*/  spl_pqueue_elem ;
struct TYPE_7__ {int /*<<< orphan*/  properties; } ;
struct TYPE_5__ {TYPE_3__* heap; int /*<<< orphan*/  flags; TYPE_4__ std; } ;
typedef  TYPE_1__ spl_heap_object ;
typedef  int /*<<< orphan*/  copy_ctor_func_t ;
struct TYPE_6__ {int flags; int count; } ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int SPL_HEAP_CORRUPTED ; 
 int /*<<< orphan*/  SPL_PQUEUE_EXTR_BOTH ; 
 int /*<<< orphan*/  ZVAL_BOOL (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_TRY_ADDREF_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_index_zval (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rebuild_object_properties (TYPE_4__*) ; 
 int /*<<< orphan*/ * spl_ce_SplPriorityQueue ; 
 int /*<<< orphan*/ * spl_gen_private_prop_name (int /*<<< orphan*/ *,char*,int) ; 
 void* spl_heap_elem (TYPE_3__*,int) ; 
 TYPE_1__* spl_heap_from_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spl_pqueue_extract_helper (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zend_hash_num_elements (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_new_array (scalar_t__) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ zval_add_ref ; 

__attribute__((used)) static HashTable* spl_heap_object_get_debug_info_helper(zend_class_entry *ce, zend_object *obj, int *is_temp) { /* {{{ */
	spl_heap_object *intern = spl_heap_from_obj(obj);
	zval tmp, heap_array;
	zend_string *pnstr;
	HashTable *debug_info;
	int  i;

	*is_temp = 1;

	if (!intern->std.properties) {
		rebuild_object_properties(&intern->std);
	}

	debug_info = zend_new_array(zend_hash_num_elements(intern->std.properties) + 1);
	zend_hash_copy(debug_info, intern->std.properties, (copy_ctor_func_t) zval_add_ref);

	pnstr = spl_gen_private_prop_name(ce, "flags", sizeof("flags")-1);
	ZVAL_LONG(&tmp, intern->flags);
	zend_hash_update(debug_info, pnstr, &tmp);
	zend_string_release_ex(pnstr, 0);

	pnstr = spl_gen_private_prop_name(ce, "isCorrupted", sizeof("isCorrupted")-1);
	ZVAL_BOOL(&tmp, intern->heap->flags&SPL_HEAP_CORRUPTED);
	zend_hash_update(debug_info, pnstr, &tmp);
	zend_string_release_ex(pnstr, 0);

	array_init(&heap_array);

	for (i = 0; i < intern->heap->count; ++i) {
		if (ce == spl_ce_SplPriorityQueue) {
			spl_pqueue_elem *pq_elem = spl_heap_elem(intern->heap, i);
			zval elem;
			spl_pqueue_extract_helper(&elem, pq_elem, SPL_PQUEUE_EXTR_BOTH);
			add_index_zval(&heap_array, i, &elem);
		} else {
			zval *elem = spl_heap_elem(intern->heap, i);
			add_index_zval(&heap_array, i, elem);
			Z_TRY_ADDREF_P(elem);
		}
	}

	pnstr = spl_gen_private_prop_name(ce, "heap", sizeof("heap")-1);
	zend_hash_update(debug_info, pnstr, &heap_array);
	zend_string_release_ex(pnstr, 0);

	return debug_info;
}