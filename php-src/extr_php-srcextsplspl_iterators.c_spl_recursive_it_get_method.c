#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_17__ {TYPE_3__* handlers; TYPE_1__* ce; } ;
typedef  TYPE_4__ zend_object ;
typedef  size_t zend_long ;
typedef  int /*<<< orphan*/  zend_function ;
struct TYPE_18__ {size_t level; TYPE_2__* iterators; } ;
typedef  TYPE_5__ spl_recursive_it_object ;
struct TYPE_16__ {int /*<<< orphan*/ * (* get_method ) (TYPE_4__**,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ;} ;
struct TYPE_15__ {int /*<<< orphan*/  zobject; } ;
struct TYPE_14__ {int /*<<< orphan*/  name; } ;
struct TYPE_13__ {int /*<<< orphan*/  function_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_ERROR ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ ) ; 
 TYPE_12__* Z_OBJCE_P (int /*<<< orphan*/ *) ; 
 TYPE_4__* Z_OBJ_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_5__* spl_recursive_it_from_obj (TYPE_4__*) ; 
 int /*<<< orphan*/ * stub1 (TYPE_4__**,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * zend_hash_find_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_std_get_method (TYPE_4__**,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static zend_function *spl_recursive_it_get_method(zend_object **zobject, zend_string *method, const zval *key)
{
	zend_function           *function_handler;
	spl_recursive_it_object *object = spl_recursive_it_from_obj(*zobject);
	zend_long                     level = object->level;
	zval                    *zobj;

	if (!object->iterators) {
		php_error_docref(NULL, E_ERROR, "The %s instance wasn't initialized properly", ZSTR_VAL((*zobject)->ce->name));
	}
	zobj = &object->iterators[level].zobject;

	function_handler = zend_std_get_method(zobject, method, key);
	if (!function_handler) {
		if ((function_handler = zend_hash_find_ptr(&Z_OBJCE_P(zobj)->function_table, method)) == NULL) {
			*zobject = Z_OBJ_P(zobj);
			function_handler = (*zobject)->handlers->get_method(zobject, method, key);
		} else {
			*zobject = Z_OBJ_P(zobj);
		}
	}
	return function_handler;
}