#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_10__ {int level; TYPE_2__* prefix; TYPE_1__* iterators; } ;
typedef  TYPE_3__ spl_recursive_it_object ;
struct TYPE_11__ {int /*<<< orphan*/  s; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ smart_str ;
struct TYPE_9__ {int /*<<< orphan*/  s; } ;
struct TYPE_8__ {int /*<<< orphan*/  ce; int /*<<< orphan*/  zobject; } ;

/* Variables and functions */
 scalar_t__ IS_TRUE ; 
 scalar_t__ IS_UNDEF ; 
 int /*<<< orphan*/  RETURN_NEW_STR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTR_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_OBJ (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smart_str_0 (TYPE_4__*) ; 
 int /*<<< orphan*/  smart_str_appendl (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_call_method_with_0_params (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spl_recursive_tree_iterator_get_prefix(spl_recursive_it_object *object, zval *return_value)
{
	smart_str  str = {0};
	zval       has_next;
	int        level;

	smart_str_appendl(&str, ZSTR_VAL(object->prefix[0].s), ZSTR_LEN(object->prefix[0].s));

	for (level = 0; level < object->level; ++level) {
		zend_call_method_with_0_params(Z_OBJ(object->iterators[level].zobject), object->iterators[level].ce, NULL, "hasnext", &has_next);
		if (Z_TYPE(has_next) != IS_UNDEF) {
			if (Z_TYPE(has_next) == IS_TRUE) {
				smart_str_appendl(&str, ZSTR_VAL(object->prefix[1].s), ZSTR_LEN(object->prefix[1].s));
			} else {
				smart_str_appendl(&str, ZSTR_VAL(object->prefix[2].s), ZSTR_LEN(object->prefix[2].s));
			}
			zval_ptr_dtor(&has_next);
		}
	}
	zend_call_method_with_0_params(Z_OBJ(object->iterators[level].zobject), object->iterators[level].ce, NULL, "hasnext", &has_next);
	if (Z_TYPE(has_next) != IS_UNDEF) {
		if (Z_TYPE(has_next) == IS_TRUE) {
			smart_str_appendl(&str, ZSTR_VAL(object->prefix[3].s), ZSTR_LEN(object->prefix[3].s));
		} else {
			smart_str_appendl(&str, ZSTR_VAL(object->prefix[4].s), ZSTR_LEN(object->prefix[4].s));
		}
		zval_ptr_dtor(&has_next);
	}

	smart_str_appendl(&str, ZSTR_VAL(object->prefix[5].s), ZSTR_LEN(object->prefix[5].s));
	smart_str_0(&str);

	RETURN_NEW_STR(str.s);
}