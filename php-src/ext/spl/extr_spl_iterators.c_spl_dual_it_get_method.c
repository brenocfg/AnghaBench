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
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_17__ {TYPE_2__* handlers; } ;
typedef  TYPE_4__ zend_object ;
typedef  int /*<<< orphan*/  zend_function ;
struct TYPE_16__ {int /*<<< orphan*/  zobject; TYPE_1__* ce; } ;
struct TYPE_18__ {TYPE_3__ inner; } ;
typedef  TYPE_5__ spl_dual_it_object ;
struct TYPE_15__ {int /*<<< orphan*/ * (* get_method ) (TYPE_4__**,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ;} ;
struct TYPE_14__ {int /*<<< orphan*/  function_table; } ;
struct TYPE_13__ {scalar_t__ get_method; } ;

/* Variables and functions */
 TYPE_4__* Z_OBJ (int /*<<< orphan*/ ) ; 
 TYPE_11__* Z_OBJ_HT (int /*<<< orphan*/ ) ; 
 TYPE_5__* spl_dual_it_from_obj (TYPE_4__*) ; 
 int /*<<< orphan*/ * stub1 (TYPE_4__**,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * zend_hash_find_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_std_get_method (TYPE_4__**,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static zend_function *spl_dual_it_get_method(zend_object **object, zend_string *method, const zval *key)
{
	zend_function        *function_handler;
	spl_dual_it_object   *intern;

	intern = spl_dual_it_from_obj(*object);

	function_handler = zend_std_get_method(object, method, key);
	if (!function_handler && intern->inner.ce) {
		if ((function_handler = zend_hash_find_ptr(&intern->inner.ce->function_table, method)) == NULL) {
			if (Z_OBJ_HT(intern->inner.zobject)->get_method) {
				*object = Z_OBJ(intern->inner.zobject);
				function_handler = (*object)->handlers->get_method(object, method, key);
			}
		} else {
			*object = Z_OBJ(intern->inner.zobject);
		}
	}
	return function_handler;
}