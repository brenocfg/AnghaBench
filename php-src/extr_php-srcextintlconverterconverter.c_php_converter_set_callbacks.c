#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int zend_bool ;
struct TYPE_5__ {scalar_t__ ce; } ;
struct TYPE_6__ {TYPE_1__ obj; } ;
typedef  TYPE_2__ php_converter_object ;
typedef  int /*<<< orphan*/  UErrorCode ;
typedef  int /*<<< orphan*/  UConverterToUCallback ;
typedef  int /*<<< orphan*/  UConverterFromUCallback ;
typedef  int /*<<< orphan*/  UConverter ;

/* Variables and functions */
 int /*<<< orphan*/  THROW_UFAILURE (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ U_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U_ZERO_ERROR ; 
 scalar_t__ php_converter_ce ; 
 scalar_t__ php_converter_from_u_callback ; 
 scalar_t__ php_converter_to_u_callback ; 
 int /*<<< orphan*/  ucnv_setFromUCallBack (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucnv_setToUCallBack (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline zend_bool php_converter_set_callbacks(php_converter_object *objval, UConverter *cnv) {
	zend_bool ret = 1;
	UErrorCode error = U_ZERO_ERROR;

	if (objval->obj.ce == php_converter_ce) {
		/* Short-circuit having to go through method calls and data marshalling
		 * when we're using default behavior
		 */
		return 1;
	}

	ucnv_setToUCallBack(cnv, (UConverterToUCallback)php_converter_to_u_callback, (const void*)objval,
                                 NULL, NULL, &error);
	if (U_FAILURE(error)) {
		THROW_UFAILURE(objval, "ucnv_setToUCallBack", error);
		ret = 0;
	}

	error = U_ZERO_ERROR;
	ucnv_setFromUCallBack(cnv, (UConverterFromUCallback)php_converter_from_u_callback, (const void*)objval,
                                    NULL, NULL, &error);
	if (U_FAILURE(error)) {
		THROW_UFAILURE(objval, "ucnv_setFromUCallBack", error);
		ret = 0;
	}
	return ret;
}