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
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_3__ {int /*<<< orphan*/  code_page; int /*<<< orphan*/  v; } ;
typedef  TYPE_1__ php_com_dotnet_object ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  LONG ;

/* Variables and functions */
 int DISPATCH_METHOD ; 
 int DISPATCH_PROPERTYGET ; 
 int /*<<< orphan*/  DISPID_VALUE ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 scalar_t__ SUCCESS ; 
 int SafeArrayGetDim (int /*<<< orphan*/ ) ; 
 scalar_t__ VT_DISPATCH ; 
 int /*<<< orphan*/  V_ARRAY (int /*<<< orphan*/ *) ; 
 scalar_t__ V_ISARRAY (int /*<<< orphan*/ *) ; 
 scalar_t__ V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_LVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  convert_to_long (int /*<<< orphan*/ *) ; 
 scalar_t__ php_com_do_invoke_by_id (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ php_com_safearray_get_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_com_saproxy_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_com_throw_exception (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  php_com_wrap_variant (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_com_zval_from_variant (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static zval *com_read_dimension(zend_object *object, zval *offset, int type, zval *rv)
{
	php_com_dotnet_object *obj;
	VARIANT v;

	ZVAL_NULL(rv);

	obj = (php_com_dotnet_object*) object;

	if (V_VT(&obj->v) == VT_DISPATCH) {
		VariantInit(&v);

		if (SUCCESS == php_com_do_invoke_by_id(obj, DISPID_VALUE,
				DISPATCH_METHOD|DISPATCH_PROPERTYGET, &v, 1, offset, 0, 0)) {
			php_com_zval_from_variant(rv, &v, obj->code_page);
			VariantClear(&v);
		}
	} else if (V_ISARRAY(&obj->v)) {
		convert_to_long(offset);

		if (SafeArrayGetDim(V_ARRAY(&obj->v)) == 1) {
			if (php_com_safearray_get_elem(&obj->v, &v, (LONG)Z_LVAL_P(offset))) {
				php_com_wrap_variant(rv, &v, obj->code_page);
				VariantClear(&v);
			}
		} else {
			php_com_saproxy_create(object, rv, offset);
		}

	} else {
		php_com_throw_exception(E_INVALIDARG, "this variant is not an array type");
	}

	return rv;
}