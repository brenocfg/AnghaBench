#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_64__   TYPE_9__ ;
typedef  struct TYPE_63__   TYPE_8__ ;
typedef  struct TYPE_62__   TYPE_7__ ;
typedef  struct TYPE_61__   TYPE_6__ ;
typedef  struct TYPE_60__   TYPE_5__ ;
typedef  struct TYPE_59__   TYPE_4__ ;
typedef  struct TYPE_58__   TYPE_3__ ;
typedef  struct TYPE_57__   TYPE_32__ ;
typedef  struct TYPE_56__   TYPE_2__ ;
typedef  struct TYPE_55__   TYPE_24__ ;
typedef  struct TYPE_54__   TYPE_23__ ;
typedef  struct TYPE_53__   TYPE_22__ ;
typedef  struct TYPE_52__   TYPE_21__ ;
typedef  struct TYPE_51__   TYPE_20__ ;
typedef  struct TYPE_50__   TYPE_1__ ;
typedef  struct TYPE_49__   TYPE_19__ ;
typedef  struct TYPE_48__   TYPE_18__ ;
typedef  struct TYPE_47__   TYPE_17__ ;
typedef  struct TYPE_46__   TYPE_16__ ;
typedef  struct TYPE_45__   TYPE_15__ ;
typedef  struct TYPE_44__   TYPE_14__ ;
typedef  struct TYPE_43__   TYPE_13__ ;
typedef  struct TYPE_42__   TYPE_12__ ;
typedef  struct TYPE_41__   TYPE_11__ ;
typedef  struct TYPE_40__   TYPE_10__ ;

/* Type definitions */
struct TYPE_52__ {int /*<<< orphan*/ * handlers; } ;
typedef  TYPE_21__ zend_object ;
struct TYPE_53__ {TYPE_10__* zf_next; TYPE_8__* zf_current; TYPE_6__* zf_key; TYPE_4__* zf_valid; TYPE_2__* zf_rewind; } ;
typedef  TYPE_22__ zend_class_iterator_funcs ;
struct TYPE_54__ {int /*<<< orphan*/  function_table; TYPE_22__* iterator_funcs_ptr; struct TYPE_54__* parent; } ;
typedef  TYPE_23__ zend_class_entry ;
struct TYPE_57__ {int /*<<< orphan*/  size; } ;
struct TYPE_55__ {TYPE_21__ std; TYPE_20__* fptr_count; TYPE_18__* fptr_offset_del; TYPE_16__* fptr_offset_has; TYPE_14__* fptr_offset_set; TYPE_12__* fptr_offset_get; int /*<<< orphan*/  flags; TYPE_32__ array; int /*<<< orphan*/  ce_get_iterator; scalar_t__ current; } ;
typedef  TYPE_24__ spl_fixedarray_object ;
struct TYPE_64__ {TYPE_23__* scope; } ;
struct TYPE_62__ {TYPE_23__* scope; } ;
struct TYPE_63__ {TYPE_7__ common; } ;
struct TYPE_60__ {TYPE_23__* scope; } ;
struct TYPE_61__ {TYPE_5__ common; } ;
struct TYPE_58__ {TYPE_23__* scope; } ;
struct TYPE_59__ {TYPE_3__ common; } ;
struct TYPE_50__ {TYPE_23__* scope; } ;
struct TYPE_56__ {TYPE_1__ common; } ;
struct TYPE_49__ {TYPE_23__* scope; } ;
struct TYPE_51__ {TYPE_19__ common; } ;
struct TYPE_47__ {TYPE_23__* scope; } ;
struct TYPE_48__ {TYPE_17__ common; } ;
struct TYPE_45__ {TYPE_23__* scope; } ;
struct TYPE_46__ {TYPE_15__ common; } ;
struct TYPE_43__ {TYPE_23__* scope; } ;
struct TYPE_44__ {TYPE_13__ common; } ;
struct TYPE_41__ {TYPE_23__* scope; } ;
struct TYPE_42__ {TYPE_11__ common; } ;
struct TYPE_40__ {TYPE_9__ common; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_COMPILE_ERROR ; 
 int /*<<< orphan*/  SPL_FIXEDARRAY_OVERLOADED_CURRENT ; 
 int /*<<< orphan*/  SPL_FIXEDARRAY_OVERLOADED_KEY ; 
 int /*<<< orphan*/  SPL_FIXEDARRAY_OVERLOADED_NEXT ; 
 int /*<<< orphan*/  SPL_FIXEDARRAY_OVERLOADED_REWIND ; 
 int /*<<< orphan*/  SPL_FIXEDARRAY_OVERLOADED_VALID ; 
 int /*<<< orphan*/  object_properties_init (TYPE_21__*,TYPE_23__*) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 TYPE_23__* spl_ce_SplFixedArray ; 
 TYPE_24__* spl_fixed_array_from_obj (TYPE_21__*) ; 
 int /*<<< orphan*/  spl_fixedarray_copy (TYPE_32__*,TYPE_32__*) ; 
 int /*<<< orphan*/  spl_fixedarray_init (TYPE_32__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spl_handler_SplFixedArray ; 
 void* zend_hash_str_find_ptr (int /*<<< orphan*/ *,char*,int) ; 
 TYPE_24__* zend_object_alloc (int,TYPE_23__*) ; 
 int /*<<< orphan*/  zend_object_std_init (TYPE_21__*,TYPE_23__*) ; 

__attribute__((used)) static zend_object *spl_fixedarray_object_new_ex(zend_class_entry *class_type, zend_object *orig, int clone_orig) /* {{{ */
{
	spl_fixedarray_object *intern;
	zend_class_entry     *parent = class_type;
	int                   inherited = 0;
	zend_class_iterator_funcs *funcs_ptr;

	intern = zend_object_alloc(sizeof(spl_fixedarray_object), parent);

	zend_object_std_init(&intern->std, class_type);
	object_properties_init(&intern->std, class_type);

	intern->current = 0;
	intern->flags = 0;

	if (orig && clone_orig) {
		spl_fixedarray_object *other = spl_fixed_array_from_obj(orig);
		intern->ce_get_iterator = other->ce_get_iterator;
		spl_fixedarray_init(&intern->array, other->array.size);
		spl_fixedarray_copy(&intern->array, &other->array);
	}

	while (parent) {
		if (parent == spl_ce_SplFixedArray) {
			intern->std.handlers = &spl_handler_SplFixedArray;
			break;
		}

		parent = parent->parent;
		inherited = 1;
	}

	if (!parent) { /* this must never happen */
		php_error_docref(NULL, E_COMPILE_ERROR, "Internal compiler error, Class is not child of SplFixedArray");
	}

	funcs_ptr = class_type->iterator_funcs_ptr;
	if (!funcs_ptr->zf_current) {
		funcs_ptr->zf_rewind = zend_hash_str_find_ptr(&class_type->function_table, "rewind", sizeof("rewind") - 1);
		funcs_ptr->zf_valid = zend_hash_str_find_ptr(&class_type->function_table, "valid", sizeof("valid") - 1);
		funcs_ptr->zf_key = zend_hash_str_find_ptr(&class_type->function_table, "key", sizeof("key") - 1);
		funcs_ptr->zf_current = zend_hash_str_find_ptr(&class_type->function_table, "current", sizeof("current") - 1);
		funcs_ptr->zf_next = zend_hash_str_find_ptr(&class_type->function_table, "next", sizeof("next") - 1);
	}
	if (inherited) {
		if (funcs_ptr->zf_rewind->common.scope  != parent) {
			intern->flags |= SPL_FIXEDARRAY_OVERLOADED_REWIND;
		}
		if (funcs_ptr->zf_valid->common.scope   != parent) {
			intern->flags |= SPL_FIXEDARRAY_OVERLOADED_VALID;
		}
		if (funcs_ptr->zf_key->common.scope     != parent) {
			intern->flags |= SPL_FIXEDARRAY_OVERLOADED_KEY;
		}
		if (funcs_ptr->zf_current->common.scope != parent) {
			intern->flags |= SPL_FIXEDARRAY_OVERLOADED_CURRENT;
		}
		if (funcs_ptr->zf_next->common.scope    != parent) {
			intern->flags |= SPL_FIXEDARRAY_OVERLOADED_NEXT;
		}

		intern->fptr_offset_get = zend_hash_str_find_ptr(&class_type->function_table, "offsetget", sizeof("offsetget") - 1);
		if (intern->fptr_offset_get->common.scope == parent) {
			intern->fptr_offset_get = NULL;
		}
		intern->fptr_offset_set = zend_hash_str_find_ptr(&class_type->function_table, "offsetset", sizeof("offsetset") - 1);
		if (intern->fptr_offset_set->common.scope == parent) {
			intern->fptr_offset_set = NULL;
		}
		intern->fptr_offset_has = zend_hash_str_find_ptr(&class_type->function_table, "offsetexists", sizeof("offsetexists") - 1);
		if (intern->fptr_offset_has->common.scope == parent) {
			intern->fptr_offset_has = NULL;
		}
		intern->fptr_offset_del = zend_hash_str_find_ptr(&class_type->function_table, "offsetunset", sizeof("offsetunset") - 1);
		if (intern->fptr_offset_del->common.scope == parent) {
			intern->fptr_offset_del = NULL;
		}
		intern->fptr_count = zend_hash_str_find_ptr(&class_type->function_table, "count", sizeof("count") - 1);
		if (intern->fptr_count->common.scope == parent) {
			intern->fptr_count = NULL;
		}
	}

	return &intern->std;
}