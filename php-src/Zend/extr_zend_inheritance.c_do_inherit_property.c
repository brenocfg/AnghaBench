#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_18__ {int flags; int /*<<< orphan*/  type; int /*<<< orphan*/  offset; } ;
typedef  TYPE_2__ zend_property_info ;
struct TYPE_19__ {int type; int /*<<< orphan*/  properties_info; TYPE_1__* parent; int /*<<< orphan*/ * name; int /*<<< orphan*/ * default_properties_table; } ;
typedef  TYPE_3__ zend_class_entry ;
typedef  scalar_t__ inheritance_status ;
struct TYPE_17__ {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_COMPILE_ERROR ; 
 scalar_t__ INHERITANCE_ERROR ; 
 scalar_t__ INHERITANCE_UNRESOLVED ; 
 int OBJ_PROP_TO_NUM (int /*<<< orphan*/ ) ; 
 scalar_t__ UNEXPECTED (int) ; 
 int ZEND_ACC_CHANGED ; 
 int ZEND_ACC_PPP_MASK ; 
 int ZEND_ACC_PRIVATE ; 
 int ZEND_ACC_PUBLIC ; 
 int ZEND_ACC_STATIC ; 
 int ZEND_INTERNAL_CLASS ; 
 int ZEND_TYPE_IS_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 TYPE_2__* Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zend_hash_append_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  add_property_compatibility_obligation (TYPE_3__*,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  emit_incompatible_property_error (TYPE_2__*,TYPE_2__*) ; 
 scalar_t__ property_types_compatible (TYPE_2__*,TYPE_2__*) ; 
 TYPE_2__* zend_duplicate_property_info_internal (TYPE_2__*) ; 
 int /*<<< orphan*/  zend_error_noreturn (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/ * zend_hash_find_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zend_visibility_string (int) ; 
 int /*<<< orphan*/  zval_ptr_dtor_nogc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void do_inherit_property(zend_property_info *parent_info, zend_string *key, zend_class_entry *ce) /* {{{ */
{
	zval *child = zend_hash_find_ex(&ce->properties_info, key, 1);
	zend_property_info *child_info;

	if (UNEXPECTED(child)) {
		child_info = Z_PTR_P(child);
		if (parent_info->flags & (ZEND_ACC_PRIVATE|ZEND_ACC_CHANGED)) {
			child_info->flags |= ZEND_ACC_CHANGED;
		}
		if (!(parent_info->flags & ZEND_ACC_PRIVATE)) {
			if (UNEXPECTED((parent_info->flags & ZEND_ACC_STATIC) != (child_info->flags & ZEND_ACC_STATIC))) {
				zend_error_noreturn(E_COMPILE_ERROR, "Cannot redeclare %s%s::$%s as %s%s::$%s",
					(parent_info->flags & ZEND_ACC_STATIC) ? "static " : "non static ", ZSTR_VAL(ce->parent->name), ZSTR_VAL(key),
					(child_info->flags & ZEND_ACC_STATIC) ? "static " : "non static ", ZSTR_VAL(ce->name), ZSTR_VAL(key));
			}

			if (UNEXPECTED((child_info->flags & ZEND_ACC_PPP_MASK) > (parent_info->flags & ZEND_ACC_PPP_MASK))) {
				zend_error_noreturn(E_COMPILE_ERROR, "Access level to %s::$%s must be %s (as in class %s)%s", ZSTR_VAL(ce->name), ZSTR_VAL(key), zend_visibility_string(parent_info->flags), ZSTR_VAL(ce->parent->name), (parent_info->flags&ZEND_ACC_PUBLIC) ? "" : " or weaker");
			} else if ((child_info->flags & ZEND_ACC_STATIC) == 0) {
				int parent_num = OBJ_PROP_TO_NUM(parent_info->offset);
				int child_num = OBJ_PROP_TO_NUM(child_info->offset);

				/* Don't keep default properties in GC (they may be freed by opcache) */
				zval_ptr_dtor_nogc(&(ce->default_properties_table[parent_num]));
				ce->default_properties_table[parent_num] = ce->default_properties_table[child_num];
				ZVAL_UNDEF(&ce->default_properties_table[child_num]);
				child_info->offset = parent_info->offset;
			}

			if (UNEXPECTED(ZEND_TYPE_IS_SET(parent_info->type))) {
				inheritance_status status = property_types_compatible(parent_info, child_info);
				if (status == INHERITANCE_ERROR) {
					emit_incompatible_property_error(child_info, parent_info);
				}
				if (status == INHERITANCE_UNRESOLVED) {
					add_property_compatibility_obligation(ce, child_info, parent_info);
				}
			} else if (UNEXPECTED(ZEND_TYPE_IS_SET(child_info->type) && !ZEND_TYPE_IS_SET(parent_info->type))) {
				zend_error_noreturn(E_COMPILE_ERROR,
						"Type of %s::$%s must not be defined (as in class %s)",
						ZSTR_VAL(ce->name),
						ZSTR_VAL(key),
						ZSTR_VAL(ce->parent->name));
			}
		}
	} else {
		if (UNEXPECTED(ce->type & ZEND_INTERNAL_CLASS)) {
			child_info = zend_duplicate_property_info_internal(parent_info);
		} else {
			child_info = parent_info;
		}
		_zend_hash_append_ptr(&ce->properties_info, key, child_info);
	}
}