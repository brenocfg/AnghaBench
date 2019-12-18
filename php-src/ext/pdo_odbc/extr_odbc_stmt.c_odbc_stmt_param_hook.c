#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  size_t zend_ulong ;
struct pdo_bound_param_data {int param_type; int max_value_len; int /*<<< orphan*/  parameter; TYPE_5__* driver_data; int /*<<< orphan*/  paramno; scalar_t__ is_param; } ;
struct TYPE_12__ {size_t st_size; } ;
struct TYPE_13__ {TYPE_1__ sb; } ;
typedef  TYPE_2__ php_stream_statbuf ;
typedef  int /*<<< orphan*/  php_stream ;
struct TYPE_14__ {scalar_t__ driver_data; } ;
typedef  TYPE_3__ pdo_stmt_t ;
struct TYPE_15__ {char* convbuf; int /*<<< orphan*/  stmt; } ;
typedef  TYPE_4__ pdo_odbc_stmt ;
struct TYPE_16__ {int len; char* outbuf; int /*<<< orphan*/  is_unicode; int /*<<< orphan*/  paramtype; } ;
typedef  TYPE_5__ pdo_odbc_param ;
typedef  enum pdo_param_event { ____Placeholder_pdo_param_event } pdo_param_event ;
typedef  int SWORD ;
typedef  int /*<<< orphan*/  SQLUSMALLINT ;
typedef  int SQLULEN ;
typedef  char* SQLPOINTER ;
typedef  int /*<<< orphan*/  RETCODE ;

/* Variables and functions */
 int /*<<< orphan*/  IS_NULL ; 
 int /*<<< orphan*/  IS_RESOURCE ; 
#define  PDO_ODBC_CONV_FAIL 140 
#define  PDO_ODBC_CONV_NOT_REQUIRED 139 
#define  PDO_ODBC_CONV_OK 138 
#define  PDO_PARAM_EVT_ALLOC 137 
#define  PDO_PARAM_EVT_EXEC_POST 136 
#define  PDO_PARAM_EVT_EXEC_PRE 135 
#define  PDO_PARAM_EVT_FETCH_POST 134 
#define  PDO_PARAM_EVT_FETCH_PRE 133 
#define  PDO_PARAM_EVT_FREE 132 
#define  PDO_PARAM_EVT_NORMALIZE 131 
 int PDO_PARAM_INPUT_OUTPUT ; 
#define  PDO_PARAM_LOB 130 
 int const PDO_PARAM_NULL ; 
#define  PDO_PARAM_STMT 129 
 int const PDO_PARAM_TYPE (int) ; 
 int /*<<< orphan*/  SQLBindParameter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,char*,int,int*) ; 
 int /*<<< orphan*/  SQLDescribeParam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int*,int*) ; 
 int SQL_BINARY ; 
 int SQL_C_BINARY ; 
 int SQL_C_CHAR ; 
 void* SQL_LEN_DATA_AT_EXEC (size_t) ; 
 int SQL_LONGVARBINARY ; 
 int SQL_LONGVARCHAR ; 
#define  SQL_NULL_DATA 128 
 int /*<<< orphan*/  SQL_PARAM_INPUT ; 
 int /*<<< orphan*/  SQL_PARAM_INPUT_OUTPUT ; 
 int /*<<< orphan*/  SQL_PARAM_OUTPUT ; 
 int /*<<< orphan*/  SQL_SUCCESS ; 
 int /*<<< orphan*/  SQL_SUCCESS_WITH_INFO ; 
 int SQL_VARBINARY ; 
 int /*<<< orphan*/  ZVAL_NEW_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ISREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Z_REFVAL (int /*<<< orphan*/ ) ; 
 size_t Z_STRLEN_P (int /*<<< orphan*/ *) ; 
 char* Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  convert_to_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (TYPE_5__*) ; 
 void* emalloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  pdo_odbc_sqltype_is_unicode (TYPE_4__*,int) ; 
 int /*<<< orphan*/  pdo_odbc_stmt_error (char*) ; 
 int /*<<< orphan*/  pdo_odbc_ucs22utf8 (TYPE_3__*,int /*<<< orphan*/ ,char*,size_t,size_t*) ; 
 int /*<<< orphan*/  pdo_odbc_utf82ucs2 (TYPE_3__*,int /*<<< orphan*/ ,char*,size_t,size_t*) ; 
 int /*<<< orphan*/  php_stream_from_zval_no_verify (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int php_stream_read (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  php_stream_stat (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  zend_string_alloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int odbc_stmt_param_hook(pdo_stmt_t *stmt, struct pdo_bound_param_data *param,
		enum pdo_param_event event_type)
{
	pdo_odbc_stmt *S = (pdo_odbc_stmt*)stmt->driver_data;
	RETCODE rc;
	SWORD sqltype = 0, ctype = 0, scale = 0, nullable = 0;
	SQLULEN precision = 0;
	pdo_odbc_param *P;
	zval *parameter;

	/* we're only interested in parameters for prepared SQL right now */
	if (param->is_param) {

		switch (event_type) {
			case PDO_PARAM_EVT_FETCH_PRE:
			case PDO_PARAM_EVT_FETCH_POST:
			case PDO_PARAM_EVT_NORMALIZE:
				/* Do nothing */
				break;

			case PDO_PARAM_EVT_FREE:
				P = param->driver_data;
				if (P) {
					efree(P);
				}
				break;

			case PDO_PARAM_EVT_ALLOC:
			{
				/* figure out what we're doing */
				switch (PDO_PARAM_TYPE(param->param_type)) {
					case PDO_PARAM_LOB:
						break;

					case PDO_PARAM_STMT:
						return 0;

					default:
						break;
				}

				rc = SQLDescribeParam(S->stmt, (SQLUSMALLINT) param->paramno+1, &sqltype, &precision, &scale, &nullable);
				if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) {
					/* MS Access, for instance, doesn't support SQLDescribeParam,
					 * so we need to guess */
					sqltype = PDO_PARAM_TYPE(param->param_type) == PDO_PARAM_LOB ?
									SQL_LONGVARBINARY :
									SQL_LONGVARCHAR;
					precision = 4000;
					scale = 5;
					nullable = 1;

					if (param->max_value_len > 0) {
						precision = param->max_value_len;
					}
				}
				if (sqltype == SQL_BINARY || sqltype == SQL_VARBINARY || sqltype == SQL_LONGVARBINARY) {
					ctype = SQL_C_BINARY;
				} else {
					ctype = SQL_C_CHAR;
				}

				P = emalloc(sizeof(*P));
				param->driver_data = P;

				P->len = 0; /* is re-populated each EXEC_PRE */
				P->outbuf = NULL;

				P->is_unicode = pdo_odbc_sqltype_is_unicode(S, sqltype);
				if (P->is_unicode) {
					/* avoid driver auto-translation: we'll do it ourselves */
					ctype = SQL_C_BINARY;
				}

				if ((param->param_type & PDO_PARAM_INPUT_OUTPUT) == PDO_PARAM_INPUT_OUTPUT) {
					P->paramtype = SQL_PARAM_INPUT_OUTPUT;
				} else if (param->max_value_len <= 0) {
					P->paramtype = SQL_PARAM_INPUT;
				} else {
					P->paramtype = SQL_PARAM_OUTPUT;
				}

				if (P->paramtype != SQL_PARAM_INPUT) {
					if (PDO_PARAM_TYPE(param->param_type) != PDO_PARAM_NULL) {
						/* need an explicit buffer to hold result */
						P->len = param->max_value_len > 0 ? param->max_value_len : precision;
						if (P->is_unicode) {
							P->len *= 2;
						}
						P->outbuf = emalloc(P->len + (P->is_unicode ? 2:1));
					}
				}

				if (PDO_PARAM_TYPE(param->param_type) == PDO_PARAM_LOB && P->paramtype != SQL_PARAM_INPUT) {
					pdo_odbc_stmt_error("Can't bind a lob for output");
					return 0;
				}

				rc = SQLBindParameter(S->stmt, (SQLUSMALLINT) param->paramno+1,
						P->paramtype, ctype, sqltype, precision, scale,
						P->paramtype == SQL_PARAM_INPUT ?
							(SQLPOINTER)param :
							P->outbuf,
						P->len,
						&P->len
						);

				if (rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO) {
					return 1;
				}
				pdo_odbc_stmt_error("SQLBindParameter");
				return 0;
			}

			case PDO_PARAM_EVT_EXEC_PRE:
				P = param->driver_data;
				if (!Z_ISREF(param->parameter)) {
					parameter = &param->parameter;
				} else {
					parameter = Z_REFVAL(param->parameter);
				}

				if (PDO_PARAM_TYPE(param->param_type) == PDO_PARAM_LOB) {
					if (Z_TYPE_P(parameter) == IS_RESOURCE) {
						php_stream *stm;
						php_stream_statbuf sb;

						php_stream_from_zval_no_verify(stm, parameter);

						if (!stm) {
							return 0;
						}

						if (0 == php_stream_stat(stm, &sb)) {
							if (P->outbuf) {
								int len, amount;
								char *ptr = P->outbuf;
								char *end = P->outbuf + P->len;

								P->len = 0;
								do {
									amount = end - ptr;
									if (amount == 0) {
										break;
									}
									if (amount > 8192)
										amount = 8192;
									len = php_stream_read(stm, ptr, amount);
									if (len == 0) {
										break;
									}
									ptr += len;
									P->len += len;
								} while (1);

							} else {
								P->len = SQL_LEN_DATA_AT_EXEC(sb.sb.st_size);
							}
						} else {
							if (P->outbuf) {
								P->len = 0;
							} else {
								P->len = SQL_LEN_DATA_AT_EXEC(0);
							}
						}
					} else {
						convert_to_string(parameter);
						if (P->outbuf) {
							P->len = Z_STRLEN_P(parameter);
							memcpy(P->outbuf, Z_STRVAL_P(parameter), P->len);
						} else {
							P->len = SQL_LEN_DATA_AT_EXEC(Z_STRLEN_P(parameter));
						}
					}
				} else if (Z_TYPE_P(parameter) == IS_NULL || PDO_PARAM_TYPE(param->param_type) == PDO_PARAM_NULL) {
					P->len = SQL_NULL_DATA;
				} else {
					convert_to_string(parameter);
					if (P->outbuf) {
						zend_ulong ulen;
						switch (pdo_odbc_utf82ucs2(stmt, P->is_unicode,
								Z_STRVAL_P(parameter),
								Z_STRLEN_P(parameter),
								&ulen)) {
							case PDO_ODBC_CONV_FAIL:
							case PDO_ODBC_CONV_NOT_REQUIRED:
								P->len = Z_STRLEN_P(parameter);
								memcpy(P->outbuf, Z_STRVAL_P(parameter), P->len);
								break;
							case PDO_ODBC_CONV_OK:
								P->len = ulen;
								memcpy(P->outbuf, S->convbuf, P->len);
								break;
						}
					} else {
						P->len = SQL_LEN_DATA_AT_EXEC(Z_STRLEN_P(parameter));
					}
				}
				return 1;

			case PDO_PARAM_EVT_EXEC_POST:
				P = param->driver_data;

				if (P->outbuf) {
					zend_ulong ulen;
					char *srcbuf;
					zend_ulong srclen = 0;

					if (Z_ISREF(param->parameter)) {
						parameter = Z_REFVAL(param->parameter);
					} else {
						parameter = &param->parameter;
					}
					zval_ptr_dtor(parameter);
					ZVAL_NULL(parameter);

					switch (P->len) {
						case SQL_NULL_DATA:
							break;
						default:
							switch (pdo_odbc_ucs22utf8(stmt, P->is_unicode, P->outbuf, P->len, &ulen)) {
								case PDO_ODBC_CONV_FAIL:
									/* something fishy, but allow it to come back as binary */
								case PDO_ODBC_CONV_NOT_REQUIRED:
									srcbuf = P->outbuf;
									srclen = P->len;
									break;
								case PDO_ODBC_CONV_OK:
									srcbuf = S->convbuf;
									srclen = ulen;
									break;
							}

							ZVAL_NEW_STR(parameter, zend_string_alloc(srclen, 0));
							memcpy(Z_STRVAL_P(parameter), srcbuf, srclen);
							Z_STRVAL_P(parameter)[Z_STRLEN_P(parameter)] = '\0';
					}
				}
				return 1;
		}
	}
	return 1;
}