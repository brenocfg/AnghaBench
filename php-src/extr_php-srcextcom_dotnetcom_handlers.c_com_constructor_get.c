#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_7__ {void* handler; int /*<<< orphan*/  fn_flags; int /*<<< orphan*/  num_args; int /*<<< orphan*/ * arg_info; TYPE_2__* scope; TYPE_1__* function_name; void* type; } ;
typedef  TYPE_3__ zend_internal_function ;
typedef  int /*<<< orphan*/  zend_function ;
struct TYPE_8__ {TYPE_2__* ce; } ;
typedef  TYPE_4__ php_com_dotnet_object ;
struct TYPE_6__ {TYPE_1__* name; } ;
struct TYPE_5__ {int* val; } ;

/* Variables and functions */
 void* ZEND_FN (int /*<<< orphan*/ ) ; 
 void* ZEND_INTERNAL_FUNCTION ; 
 int /*<<< orphan*/  com_create_instance ; 
 int /*<<< orphan*/  com_variant_create_instance ; 

__attribute__((used)) static zend_function *com_constructor_get(zend_object *object)
{
	php_com_dotnet_object *obj = (php_com_dotnet_object *) object;
	static zend_internal_function c, d, v;

#define POPULATE_CTOR(f, fn)	\
	f.type = ZEND_INTERNAL_FUNCTION; \
	f.function_name = obj->ce->name; \
	f.scope = obj->ce; \
	f.arg_info = NULL; \
	f.num_args = 0; \
	f.fn_flags = 0; \
	f.handler = ZEND_FN(fn); \
	return (zend_function*)&f;

	switch (obj->ce->name->val[0]) {
#if HAVE_MSCOREE_H
		case 'd':
			POPULATE_CTOR(d, com_dotnet_create_instance);
#endif

		case 'c':
			POPULATE_CTOR(c, com_create_instance);

		case 'v':
			POPULATE_CTOR(v, com_variant_create_instance);

		default:
			return NULL;
	}
}