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
typedef  int /*<<< orphan*/  ub4 ;
typedef  int /*<<< orphan*/  ub2 ;
typedef  int /*<<< orphan*/  ub1 ;
typedef  int /*<<< orphan*/  sb4 ;
struct TYPE_2__ {int dtype; int /*<<< orphan*/  indicator; int /*<<< orphan*/  datalen; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ pdo_oci_column ;
typedef  int /*<<< orphan*/  dvoid ;
typedef  int /*<<< orphan*/  OCIDefine ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int /*<<< orphan*/  OCI_CONTINUE ; 
 int /*<<< orphan*/  OCI_ERROR ; 
 int /*<<< orphan*/  OCI_ONE_PIECE ; 
#define  SQLT_BLOB 129 
#define  SQLT_CLOB 128 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static sb4 oci_define_callback(dvoid *octxp, OCIDefine *define, ub4 iter, dvoid **bufpp,
		ub4 **alenpp, ub1 *piecep, dvoid **indpp, ub2 **rcodepp)
{
	pdo_oci_column *col = (pdo_oci_column*)octxp;

	switch (col->dtype) {
		case SQLT_BLOB:
		case SQLT_CLOB:
			*piecep = OCI_ONE_PIECE;
			*bufpp = col->data;
			*alenpp = &col->datalen;
			*indpp = (dvoid *)&col->indicator;
			break;

		default:
			php_error_docref(NULL, E_WARNING,
				"unhandled datatype in oci_define_callback; this should not happen");
			return OCI_ERROR;
	}

	return OCI_CONTINUE;
}