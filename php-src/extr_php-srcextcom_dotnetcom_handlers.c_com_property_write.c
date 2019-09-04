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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_3__ {int /*<<< orphan*/  v; } ;
typedef  TYPE_1__ php_com_dotnet_object ;
typedef  int /*<<< orphan*/  VARIANT ;

/* Variables and functions */
 int DISPATCH_PROPERTYPUT ; 
 int DISPATCH_PROPERTYPUTREF ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 scalar_t__ SUCCESS ; 
 scalar_t__ VT_DISPATCH ; 
 scalar_t__ V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTR_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 scalar_t__ php_com_do_invoke (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_com_throw_exception (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static zval *com_property_write(zend_object *object, zend_string *member, zval *value, void **cache_slot)
{
	php_com_dotnet_object *obj;
	VARIANT v;

	obj = (php_com_dotnet_object*) object;

	if (V_VT(&obj->v) == VT_DISPATCH) {
		VariantInit(&v);

		if (SUCCESS == php_com_do_invoke(obj, ZSTR_VAL(member), ZSTR_LEN(member),
				DISPATCH_PROPERTYPUT|DISPATCH_PROPERTYPUTREF, &v, 1, value, 0)) {
			VariantClear(&v);
		}
	} else {
		php_com_throw_exception(E_INVALIDARG, "this variant has no properties");
	}
	return value;
}