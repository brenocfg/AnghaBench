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
struct TYPE_3__ {int /*<<< orphan*/  code_page; int /*<<< orphan*/  v; } ;
typedef  TYPE_1__ php_com_dotnet_object ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int DISPATCH_METHOD ; 
 int DISPATCH_PROPERTYGET ; 
 scalar_t__ DISP_E_BADPARAMCOUNT ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 scalar_t__ SUCCESS ; 
 scalar_t__ VT_DISPATCH ; 
 scalar_t__ V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTR_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ php_com_do_invoke (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  php_com_saproxy_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_com_throw_exception (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  php_com_zval_from_variant (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static zval *com_property_read(zend_object *object, zend_string *member, int type, void **cahce_slot, zval *rv)
{
	php_com_dotnet_object *obj;
	VARIANT v;
	HRESULT res;

	ZVAL_NULL(rv);

	obj = (php_com_dotnet_object*) object;

	if (V_VT(&obj->v) == VT_DISPATCH) {
		VariantInit(&v);

		res = php_com_do_invoke(obj, ZSTR_VAL(member), ZSTR_LEN(member),
				DISPATCH_METHOD|DISPATCH_PROPERTYGET, &v, 0, NULL, 1);

		if (res == SUCCESS) {
			php_com_zval_from_variant(rv, &v, obj->code_page);
			VariantClear(&v);
		} else if (res == DISP_E_BADPARAMCOUNT) {
			zval zv;

			ZVAL_STR(&zv, member);
			php_com_saproxy_create(object, rv, &zv);
		}
	} else {
		php_com_throw_exception(E_INVALIDARG, "this variant has no properties");
	}

	return rv;
}