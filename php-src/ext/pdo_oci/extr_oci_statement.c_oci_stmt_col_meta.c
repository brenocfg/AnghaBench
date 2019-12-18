#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  scalar_t__ zend_long ;
typedef  int ub2 ;
typedef  scalar_t__ ub1 ;
typedef  int sb1 ;
struct TYPE_4__ {scalar_t__ column_count; scalar_t__ driver_data; } ;
typedef  TYPE_1__ pdo_stmt_t ;
struct TYPE_5__ {int /*<<< orphan*/  err; int /*<<< orphan*/  stmt; } ;
typedef  TYPE_2__ pdo_oci_stmt ;
typedef  int /*<<< orphan*/  dvoid ;
typedef  int /*<<< orphan*/  OCIParam ;

/* Variables and functions */
 int FAILURE ; 
 int /*<<< orphan*/  OCIAttrGet ; 
 int /*<<< orphan*/  OCIDescriptorFree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OCIParamGet ; 
 int /*<<< orphan*/  OCI_ATTR_CHARSET_FORM ; 
 int /*<<< orphan*/  OCI_ATTR_DATA_TYPE ; 
 int /*<<< orphan*/  OCI_ATTR_IS_NULL ; 
 int /*<<< orphan*/  OCI_ATTR_PRECISION ; 
 int /*<<< orphan*/  OCI_ATTR_SCALE ; 
 int /*<<< orphan*/  OCI_DTYPE_PARAM ; 
 int /*<<< orphan*/  OCI_HTYPE_STMT ; 
 int PDO_PARAM_LOB ; 
 int PDO_PARAM_STR ; 
 scalar_t__ SQLCS_NCHAR ; 
#define  SQLT_AFC 149 
#define  SQLT_BDOUBLE 148 
#define  SQLT_BFILE 147 
#define  SQLT_BFLOAT 146 
#define  SQLT_BIN 145 
#define  SQLT_BLOB 144 
#define  SQLT_CHR 143 
#define  SQLT_CLOB 142 
#define  SQLT_DAT 141 
#define  SQLT_FLT 140 
#define  SQLT_IBDOUBLE 139 
#define  SQLT_IBFLOAT 138 
#define  SQLT_INTERVAL_DS 137 
#define  SQLT_INTERVAL_YM 136 
#define  SQLT_LBI 135 
#define  SQLT_LNG 134 
#define  SQLT_NUM 133 
#define  SQLT_RDD 132 
#define  SQLT_TIMESTAMP 131 
#define  SQLT_TIMESTAMP_LTZ 130 
#define  SQLT_TIMESTAMP_TZ 129 
#define  SQLT_VCS 128 
 int /*<<< orphan*/  STMT_CALL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STMT_CALL_MSG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int SUCCESS ; 
 int /*<<< orphan*/  add_assoc_long (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  add_assoc_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  add_assoc_zval (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_next_index_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int oci_stmt_col_meta(pdo_stmt_t *stmt, zend_long colno, zval *return_value) /* {{{ */
{
	pdo_oci_stmt *S = (pdo_oci_stmt*)stmt->driver_data;
	OCIParam *param = NULL;
	ub2 dtype, precis;
	sb1 scale;
	zval flags;
	ub1 isnull, charset_form;
	if (!S->stmt) {
		return FAILURE;
	}
	if (colno >= stmt->column_count) {
		/* error invalid column */
		return FAILURE;
	}

	array_init(return_value);
	array_init(&flags);

	/* describe the column */
	STMT_CALL(OCIParamGet, (S->stmt, OCI_HTYPE_STMT, S->err, (dvoid*)&param, colno+1));

	/* column data type */
	STMT_CALL_MSG(OCIAttrGet, "OCI_ATTR_DATA_TYPE",
			(param, OCI_DTYPE_PARAM, &dtype, 0, OCI_ATTR_DATA_TYPE, S->err));

	/* column precision */
	STMT_CALL_MSG(OCIAttrGet, "OCI_ATTR_PRECISION",
			(param, OCI_DTYPE_PARAM, &precis, 0, OCI_ATTR_PRECISION, S->err));

	/* column scale */
	STMT_CALL_MSG(OCIAttrGet, "OCI_ATTR_SCALE",
			(param, OCI_DTYPE_PARAM, &scale, 0, OCI_ATTR_SCALE, S->err));

	/* string column charset form */
	if (dtype == SQLT_CHR || dtype == SQLT_VCS || dtype == SQLT_AFC || dtype == SQLT_CLOB) {
		STMT_CALL_MSG(OCIAttrGet, "OCI_ATTR_CHARSET_FORM",
			(param, OCI_DTYPE_PARAM, &charset_form, 0, OCI_ATTR_CHARSET_FORM, S->err));
	}


	if (dtype) {
	/* if there is a declared type */
		switch (dtype) {
#ifdef SQLT_TIMESTAMP
		case SQLT_TIMESTAMP:
			add_assoc_string(return_value, "oci:decl_type", "TIMESTAMP");
			add_assoc_string(return_value, "native_type", "TIMESTAMP");
			break;
#endif
#ifdef SQLT_TIMESTAMP_TZ
		case SQLT_TIMESTAMP_TZ:
			add_assoc_string(return_value, "oci:decl_type", "TIMESTAMP WITH TIMEZONE");
			add_assoc_string(return_value, "native_type", "TIMESTAMP WITH TIMEZONE");
			break;
#endif
#ifdef SQLT_TIMESTAMP_LTZ
		case SQLT_TIMESTAMP_LTZ:
			add_assoc_string(return_value, "oci:decl_type", "TIMESTAMP WITH LOCAL TIMEZONE");
			add_assoc_string(return_value, "native_type", "TIMESTAMP WITH LOCAL TIMEZONE");
			break;
#endif
#ifdef SQLT_INTERVAL_YM
		case SQLT_INTERVAL_YM:
			add_assoc_string(return_value, "oci:decl_type", "INTERVAL YEAR TO MONTH");
			add_assoc_string(return_value, "native_type", "INTERVAL YEAR TO MONTH");
			break;
#endif
#ifdef SQLT_INTERVAL_DS
		case SQLT_INTERVAL_DS:
			add_assoc_string(return_value, "oci:decl_type", "INTERVAL DAY TO SECOND");
			add_assoc_string(return_value, "native_type", "INTERVAL DAY TO SECOND");
			break;
#endif
		case SQLT_DAT:
			add_assoc_string(return_value, "oci:decl_type", "DATE");
			add_assoc_string(return_value, "native_type", "DATE");
			break;
		case SQLT_FLT :
		case SQLT_NUM:
			/* if the precision is nonzero and scale is -127 then it is a FLOAT */
			if (scale == -127 && precis != 0) {
				add_assoc_string(return_value, "oci:decl_type", "FLOAT");
				add_assoc_string(return_value, "native_type", "FLOAT");
			} else {
				add_assoc_string(return_value, "oci:decl_type", "NUMBER");
				add_assoc_string(return_value, "native_type", "NUMBER");
			}
			break;
		case SQLT_LNG:
			add_assoc_string(return_value, "oci:decl_type", "LONG");
			add_assoc_string(return_value, "native_type", "LONG");
			break;
		case SQLT_BIN:
			add_assoc_string(return_value, "oci:decl_type", "RAW");
			add_assoc_string(return_value, "native_type", "RAW");
			break;
		case SQLT_LBI:
			add_assoc_string(return_value, "oci:decl_type", "LONG RAW");
			add_assoc_string(return_value, "native_type", "LONG RAW");
			break;
		case SQLT_CHR:
		case SQLT_VCS:
			if (charset_form == SQLCS_NCHAR) {
				add_assoc_string(return_value, "oci:decl_type", "NVARCHAR2");
				add_assoc_string(return_value, "native_type", "NVARCHAR2");
			} else {
				add_assoc_string(return_value, "oci:decl_type", "VARCHAR2");
				add_assoc_string(return_value, "native_type", "VARCHAR2");
			}
			break;
		case SQLT_AFC:
			if (charset_form == SQLCS_NCHAR) {
				add_assoc_string(return_value, "oci:decl_type", "NCHAR");
				add_assoc_string(return_value, "native_type", "NCHAR");
			} else {
				add_assoc_string(return_value, "oci:decl_type", "CHAR");
				add_assoc_string(return_value, "native_type", "CHAR");
			}
			break;
		case SQLT_BLOB:
			add_assoc_string(return_value, "oci:decl_type", "BLOB");
			add_next_index_string(&flags, "blob");
			add_assoc_string(return_value, "native_type", "BLOB");
			break;
		case SQLT_CLOB:
			if (charset_form == SQLCS_NCHAR) {
				add_assoc_string(return_value, "oci:decl_type", "NCLOB");
				add_assoc_string(return_value, "native_type", "NCLOB");
			} else {
				add_assoc_string(return_value, "oci:decl_type", "CLOB");
				add_assoc_string(return_value, "native_type", "CLOB");
			}
			add_next_index_string(&flags, "blob");
			break;
		case SQLT_BFILE:
			add_assoc_string(return_value, "oci:decl_type", "BFILE");
			add_next_index_string(&flags, "blob");
			add_assoc_string(return_value, "native_type", "BFILE");
			break;
		case SQLT_RDD:
			add_assoc_string(return_value, "oci:decl_type", "ROWID");
			add_assoc_string(return_value, "native_type", "ROWID");
			break;
		case SQLT_BFLOAT:
		case SQLT_IBFLOAT:
			add_assoc_string(return_value, "oci:decl_type", "BINARY_FLOAT");
			add_assoc_string(return_value, "native_type", "BINARY_FLOAT");
			break;
		case SQLT_BDOUBLE:
		case SQLT_IBDOUBLE:
			add_assoc_string(return_value, "oci:decl_type", "BINARY_DOUBLE");
			add_assoc_string(return_value, "native_type", "BINARY_DOUBLE");
			break;
		default:
			add_assoc_long(return_value, "oci:decl_type", dtype);
			add_assoc_string(return_value, "native_type", "UNKNOWN");
		}
	} else {
		/* if the column is NULL */
		add_assoc_long(return_value, "oci:decl_type", 0);
		add_assoc_string(return_value, "native_type", "NULL");
	}

	/* column can be null */
	STMT_CALL_MSG(OCIAttrGet, "OCI_ATTR_IS_NULL",
			(param, OCI_DTYPE_PARAM, &isnull, 0, OCI_ATTR_IS_NULL, S->err));

	if (isnull) {
		add_next_index_string(&flags, "nullable");
	} else {
		add_next_index_string(&flags, "not_null");
	}

	/* PDO type */
	switch (dtype) {
		case SQLT_BFILE:
		case SQLT_BLOB:
		case SQLT_CLOB:
			add_assoc_long(return_value, "pdo_type", PDO_PARAM_LOB);
			break;
		default:
			add_assoc_long(return_value, "pdo_type", PDO_PARAM_STR);
	}

	add_assoc_long(return_value, "scale", scale);
	add_assoc_zval(return_value, "flags", &flags);

	OCIDescriptorFree(param, OCI_DTYPE_PARAM);
	return SUCCESS;
}