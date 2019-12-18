#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ zend_bool ;
typedef  int ub4 ;
typedef  int ub2 ;
typedef  int /*<<< orphan*/  text ;
struct pdo_column_data {int precision; int maxlen; void* param_type; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {struct pdo_column_data* columns; scalar_t__ driver_data; } ;
typedef  TYPE_3__ pdo_stmt_t ;
struct TYPE_9__ {TYPE_2__* cols; int /*<<< orphan*/  err; int /*<<< orphan*/  stmt; TYPE_1__* H; } ;
typedef  TYPE_4__ pdo_oci_stmt ;
typedef  int /*<<< orphan*/  dvoid ;
struct TYPE_7__ {int dtype; int datalen; int /*<<< orphan*/  def; int /*<<< orphan*/  retcode; int /*<<< orphan*/  fetched_len; int /*<<< orphan*/  indicator; void* data; } ;
struct TYPE_6__ {int max_char_width; int /*<<< orphan*/  env; } ;
typedef  int /*<<< orphan*/  OCIParam ;
typedef  int /*<<< orphan*/  OCILobLocator ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  OCIAttrGet ; 
 int /*<<< orphan*/  OCIDefineByPos ; 
 int /*<<< orphan*/  OCIDefineDynamic ; 
 int /*<<< orphan*/  OCIDescriptorAlloc ; 
 int /*<<< orphan*/  OCIParamGet ; 
 int /*<<< orphan*/  OCI_ATTR_DATA_SIZE ; 
 int /*<<< orphan*/  OCI_ATTR_DATA_TYPE ; 
 int /*<<< orphan*/  OCI_ATTR_NAME ; 
 int /*<<< orphan*/  OCI_ATTR_PRECISION ; 
 int /*<<< orphan*/  OCI_DEFAULT ; 
 int /*<<< orphan*/  OCI_DTYPE_LOB ; 
 int /*<<< orphan*/  OCI_DTYPE_PARAM ; 
 int /*<<< orphan*/  OCI_DYNAMIC_FETCH ; 
 int /*<<< orphan*/  OCI_HTYPE_STMT ; 
 void* PDO_PARAM_LOB ; 
 void* PDO_PARAM_STR ; 
#define  SQLT_BIN 132 
#define  SQLT_BLOB 131 
 int SQLT_CHR ; 
#define  SQLT_CLOB 130 
 int SQLT_DAT ; 
 int SQLT_IBDOUBLE ; 
 int SQLT_IBFLOAT ; 
#define  SQLT_LBI 129 
#define  SQLT_LNG 128 
 int SQLT_NUM ; 
 int SQLT_RDD ; 
 int SQLT_TIMESTAMP ; 
 int SQLT_TIMESTAMP_TZ ; 
 int /*<<< orphan*/  STMT_CALL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STMT_CALL_MSG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 void* emalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oci_define_callback ; 
 int /*<<< orphan*/  zend_string_init (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int oci_stmt_describe(pdo_stmt_t *stmt, int colno) /* {{{ */
{
	pdo_oci_stmt *S = (pdo_oci_stmt*)stmt->driver_data;
	OCIParam *param = NULL;
	text *colname;
	ub2 dtype, data_size, precis;
	ub4 namelen;
	struct pdo_column_data *col = &stmt->columns[colno];
	zend_bool dyn = FALSE;

	/* describe the column */
	STMT_CALL(OCIParamGet, (S->stmt, OCI_HTYPE_STMT, S->err, (dvoid*)&param, colno+1));

	/* what type ? */
	STMT_CALL_MSG(OCIAttrGet, "OCI_ATTR_DATA_TYPE",
			(param, OCI_DTYPE_PARAM, &dtype, 0, OCI_ATTR_DATA_TYPE, S->err));

	/* how big ? */
	STMT_CALL_MSG(OCIAttrGet, "OCI_ATTR_DATA_SIZE",
			(param, OCI_DTYPE_PARAM, &data_size, 0, OCI_ATTR_DATA_SIZE, S->err));

	/* precision ? */
	STMT_CALL_MSG(OCIAttrGet, "OCI_ATTR_PRECISION",
			(param, OCI_DTYPE_PARAM, &precis, 0, OCI_ATTR_PRECISION, S->err));

	/* name ? */
	STMT_CALL_MSG(OCIAttrGet, "OCI_ATTR_NAME",
			(param, OCI_DTYPE_PARAM, &colname, &namelen, OCI_ATTR_NAME, S->err));

	col->precision = precis;
	col->maxlen = data_size;
	col->name = zend_string_init((char *)colname, namelen, 0);

	S->cols[colno].dtype = dtype;

	/* how much room do we need to store the field */
	switch (dtype) {
		case SQLT_LBI:
		case SQLT_LNG:
			if (dtype == SQLT_LBI) {
				dtype = SQLT_BIN;
			} else {
				dtype = SQLT_CHR;
			}
			S->cols[colno].datalen = 512; /* XXX should be INT_MAX and fetched by pieces */
			S->cols[colno].data = emalloc(S->cols[colno].datalen + 1);
			col->param_type = PDO_PARAM_STR;
			break;

		case SQLT_BLOB:
		case SQLT_CLOB:
			col->param_type = PDO_PARAM_LOB;
			STMT_CALL(OCIDescriptorAlloc, (S->H->env, (dvoid**)&S->cols[colno].data, OCI_DTYPE_LOB, 0, NULL));
			S->cols[colno].datalen = sizeof(OCILobLocator*);
			dyn = TRUE;
			break;

		case SQLT_BIN:
		default:
			if (dtype == SQLT_DAT || dtype == SQLT_NUM || dtype == SQLT_RDD
#ifdef SQLT_TIMESTAMP
					|| dtype == SQLT_TIMESTAMP
#endif
#ifdef SQLT_TIMESTAMP_TZ
					|| dtype == SQLT_TIMESTAMP_TZ
#endif
					) {
				/* should be big enough for most date formats and numbers */
				S->cols[colno].datalen = 512;
#if defined(SQLT_IBFLOAT) && defined(SQLT_IBDOUBLE)
			} else if (dtype == SQLT_IBFLOAT || dtype == SQLT_IBDOUBLE) {
				S->cols[colno].datalen = 1024;
#endif
			} else if (dtype == SQLT_BIN) {
				S->cols[colno].datalen = (ub4) col->maxlen * 2; /* raw characters to hex digits */
			} else {
				S->cols[colno].datalen = (ub4) (col->maxlen * S->H->max_char_width);
			}

			S->cols[colno].data = emalloc(S->cols[colno].datalen + 1);
			dtype = SQLT_CHR;

			/* returning data as a string */
			col->param_type = PDO_PARAM_STR;
	}

	STMT_CALL(OCIDefineByPos, (S->stmt, &S->cols[colno].def, S->err, colno+1,
				S->cols[colno].data, S->cols[colno].datalen, dtype, &S->cols[colno].indicator,
				&S->cols[colno].fetched_len, &S->cols[colno].retcode, dyn ? OCI_DYNAMIC_FETCH : OCI_DEFAULT));

	if (dyn) {
		STMT_CALL(OCIDefineDynamic, (S->cols[colno].def, S->err, &S->cols[colno],
				oci_define_callback));
	}

	return 1;
}