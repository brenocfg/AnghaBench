#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_6__ {int /*<<< orphan*/  code_page; } ;
typedef  TYPE_1__ php_com_dotnet_object ;
typedef  int WORD ;
typedef  int /*<<< orphan*/  VARIANT ;
struct TYPE_7__ {int cArgs; int cNamedArgs; int /*<<< orphan*/ * rgdispidNamedArgs; int /*<<< orphan*/ * rgvarg; } ;
typedef  scalar_t__ HRESULT ;
typedef  TYPE_2__ DISPPARAMS ;
typedef  int /*<<< orphan*/  DISPID ;

/* Variables and functions */
 int DISPATCH_PROPERTYPUT ; 
 int /*<<< orphan*/  DISPID_PROPERTYPUT ; 
 scalar_t__ DISP_E_BADPARAMCOUNT ; 
 int FAILURE ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 int SUCCESS ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (int /*<<< orphan*/ *) ; 
 scalar_t__ php_com_invoke_helper (TYPE_1__*,int /*<<< orphan*/ ,int,TYPE_2__*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  php_com_variant_from_zval (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ safe_emalloc (int,int,int /*<<< orphan*/ ) ; 

int php_com_do_invoke_by_id(php_com_dotnet_object *obj, DISPID dispid,
		WORD flags,	VARIANT *v, int nargs, zval *args, int silent, int allow_noarg)
{
	DISPID altdispid;
	DISPPARAMS disp_params;
	HRESULT hr;
	VARIANT *vargs = NULL;
	int i;

	if (nargs) {
		vargs = (VARIANT*)safe_emalloc(sizeof(VARIANT), nargs, 0);
	}

	/* Invoke'd args are in reverse order */
	for (i = 0; i < nargs; i++) {
		php_com_variant_from_zval(&vargs[i], &args[nargs - i - 1], obj->code_page);
	}

	disp_params.cArgs = nargs;
	disp_params.cNamedArgs = 0;
	disp_params.rgvarg = vargs;
	disp_params.rgdispidNamedArgs = NULL;

	if (flags & DISPATCH_PROPERTYPUT) {
		altdispid = DISPID_PROPERTYPUT;
		disp_params.rgdispidNamedArgs = &altdispid;
		disp_params.cNamedArgs = 1;
	}

	/* this will create an exception if needed */
	hr = php_com_invoke_helper(obj, dispid, flags, &disp_params, v, silent, allow_noarg);

	/* release variants */
	if (vargs) {
		for (i = 0; i < nargs; i++) {
			VariantClear(&vargs[i]);
		}
		efree(vargs);
	}

	/* a bit of a hack this, but it's needed for COM array access. */
	if (hr == DISP_E_BADPARAMCOUNT)
		return hr;

	return SUCCEEDED(hr) ? SUCCESS : FAILURE;
}