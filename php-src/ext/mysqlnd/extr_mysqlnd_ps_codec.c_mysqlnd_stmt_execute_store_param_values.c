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
typedef  int /*<<< orphan*/  zend_uchar ;
struct TYPE_5__ {unsigned int param_count; TYPE_1__* param_bind; } ;
struct TYPE_4__ {int type; int flags; int /*<<< orphan*/  zv; } ;
typedef  TYPE_2__ MYSQLND_STMT_DATA ;

/* Variables and functions */
 scalar_t__ IS_NULL ; 
 scalar_t__ IS_STRING ; 
 int MYSQLND_PARAM_BIND_BLOB_USED ; 
#define  MYSQL_TYPE_DOUBLE 133 
#define  MYSQL_TYPE_LONG 132 
#define  MYSQL_TYPE_LONGLONG 131 
#define  MYSQL_TYPE_LONG_BLOB 130 
#define  MYSQL_TYPE_TINY 129 
#define  MYSQL_TYPE_VAR_STRING 128 
 int /*<<< orphan*/  ZVAL_DEREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_DVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ISUNDEF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_ISUNDEF_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_LVAL_P (int /*<<< orphan*/ *) ; 
 size_t Z_STRLEN_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  convert_to_double_ex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  float8store (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int1store (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int4store (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int8store (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t const) ; 
 int /*<<< orphan*/ * php_mysqlnd_net_store_length (int /*<<< orphan*/ *,size_t const) ; 

__attribute__((used)) static void
mysqlnd_stmt_execute_store_param_values(MYSQLND_STMT_DATA * stmt, zval * copies, zend_uchar * buf, zend_uchar ** p, size_t null_byte_offset)
{
	unsigned int i;
	for (i = 0; i < stmt->param_count; i++) {
		zval *data, *parameter = &stmt->param_bind[i].zv;

		ZVAL_DEREF(parameter);
		data = (copies && !Z_ISUNDEF(copies[i]))? &copies[i]: parameter;
		/* Handle long data */
		if (!Z_ISUNDEF_P(parameter) && Z_TYPE_P(data) == IS_NULL) {
			(buf + null_byte_offset)[i/8] |= (zend_uchar) (1 << (i & 7));
		} else {
			switch (stmt->param_bind[i].type) {
				case MYSQL_TYPE_DOUBLE:
					convert_to_double_ex(data);
					float8store(*p, Z_DVAL_P(data));
					(*p) += 8;
					break;
				case MYSQL_TYPE_LONGLONG:
					if (Z_TYPE_P(data) == IS_STRING) {
						goto send_string;
					}
					/* data has alreade been converted to long */
					int8store(*p, Z_LVAL_P(data));
					(*p) += 8;
					break;
				case MYSQL_TYPE_LONG:
					if (Z_TYPE_P(data) == IS_STRING) {
						goto send_string;
					}
					/* data has alreade been converted to long */
					int4store(*p, Z_LVAL_P(data));
					(*p) += 4;
					break;
				case MYSQL_TYPE_TINY:
					if (Z_TYPE_P(data) == IS_STRING) {
						goto send_string;
					}
					int1store(*p, Z_LVAL_P(data));
					(*p)++;
					break;
				case MYSQL_TYPE_LONG_BLOB:
					if (stmt->param_bind[i].flags & MYSQLND_PARAM_BIND_BLOB_USED) {
						stmt->param_bind[i].flags &= ~MYSQLND_PARAM_BIND_BLOB_USED;
					} else {
						/* send_long_data() not called, send empty string */
						*p = php_mysqlnd_net_store_length(*p, 0);
					}
					break;
				case MYSQL_TYPE_VAR_STRING:
send_string:
					{
						const size_t len = Z_STRLEN_P(data);
						/* to is after p. The latter hasn't been moved */
						*p = php_mysqlnd_net_store_length(*p, len);
						memcpy(*p, Z_STRVAL_P(data), len);
						(*p) += len;
					}
					break;
				default:
					/* Won't happen, but set to NULL */
					(buf + null_byte_offset)[i/8] |= (zend_uchar) (1 << (i & 7));
					break;
			}
		}
	}
}