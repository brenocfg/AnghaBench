#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_3__ {scalar_t__ id_of_name_cache; scalar_t__ method_cache; int /*<<< orphan*/  v; int /*<<< orphan*/ * sink_dispatch; int /*<<< orphan*/ * typeinfo; } ;
typedef  TYPE_1__ php_com_dotnet_object ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FREE_HASHTABLE (scalar_t__) ; 
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeInfo_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_com_object_enable_event_sink (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_destroy (scalar_t__) ; 
 int /*<<< orphan*/  zend_object_std_dtor (int /*<<< orphan*/ *) ; 

void php_com_object_free_storage(zend_object *object)
{
	php_com_dotnet_object *obj = (php_com_dotnet_object*)object;

	if (obj->typeinfo) {
		ITypeInfo_Release(obj->typeinfo);
		obj->typeinfo = NULL;
	}

	if (obj->sink_dispatch) {
		php_com_object_enable_event_sink(obj, FALSE);
		IDispatch_Release(obj->sink_dispatch);
		obj->sink_dispatch = NULL;
	}

	VariantClear(&obj->v);

	if (obj->method_cache) {
		zend_hash_destroy(obj->method_cache);
		FREE_HASHTABLE(obj->method_cache);
	}
	if (obj->id_of_name_cache) {
		zend_hash_destroy(obj->id_of_name_cache);
		FREE_HASHTABLE(obj->id_of_name_cache);
	}

	zend_object_std_dtor(object);
}