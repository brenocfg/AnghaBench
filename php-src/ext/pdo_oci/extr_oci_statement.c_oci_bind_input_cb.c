#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int ub4 ;
typedef  int /*<<< orphan*/  ub1 ;
struct pdo_bound_param_data {int /*<<< orphan*/  parameter; scalar_t__ driver_data; } ;
typedef  int /*<<< orphan*/  sb4 ;
struct TYPE_2__ {int indicator; int* thing; } ;
typedef  TYPE_1__ pdo_oci_bound_param ;
typedef  int dvoid ;
typedef  int /*<<< orphan*/  OCIBind ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int /*<<< orphan*/  OCI_CONTINUE ; 
 int /*<<< orphan*/  OCI_ERROR ; 
 int /*<<< orphan*/  OCI_ONE_PIECE ; 
 scalar_t__ ZVAL_IS_NULL (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_ISREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Z_REFVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_STRLEN_P (int /*<<< orphan*/ *) ; 
 int* Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  try_convert_to_string (int /*<<< orphan*/ *) ; 

__attribute__((used)) static sb4 oci_bind_input_cb(dvoid *ctx, OCIBind *bindp, ub4 iter, ub4 index, dvoid **bufpp, ub4 *alenp, ub1 *piecep, dvoid **indpp) /* {{{ */
{
	struct pdo_bound_param_data *param = (struct pdo_bound_param_data*)ctx;
	pdo_oci_bound_param *P = (pdo_oci_bound_param*)param->driver_data;
	zval *parameter;

	if (!param) {
		php_error_docref(NULL, E_WARNING, "param is NULL in oci_bind_input_cb; this should not happen");
		return OCI_ERROR;
	}

	*indpp = &P->indicator;

    if (Z_ISREF(param->parameter))
		parameter = Z_REFVAL(param->parameter);
	else
		parameter = &param->parameter;

	if (P->thing) {
		*bufpp = P->thing;
		*alenp = sizeof(void*);
	} else if (ZVAL_IS_NULL(parameter)) {
		/* insert a NULL value into the column */
		P->indicator = -1; /* NULL */
		*bufpp = 0;
		*alenp = -1;
	} else if (!P->thing) {
		/* regular string bind */
		if (!try_convert_to_string(parameter)) {
			return OCI_ERROR;
		}
		*bufpp = Z_STRVAL_P(parameter);
		*alenp = (ub4) Z_STRLEN_P(parameter);
	}

	*piecep = OCI_ONE_PIECE;
	return OCI_CONTINUE;
}