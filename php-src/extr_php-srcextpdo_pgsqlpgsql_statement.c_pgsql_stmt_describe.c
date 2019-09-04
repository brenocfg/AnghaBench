#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_long ;
struct pdo_column_data {void* param_type; int /*<<< orphan*/  name; int /*<<< orphan*/  precision; int /*<<< orphan*/  maxlen; } ;
struct pdo_bound_param_data {int /*<<< orphan*/  param_type; } ;
struct TYPE_6__ {int /*<<< orphan*/  bound_columns; struct pdo_column_data* columns; scalar_t__ driver_data; } ;
typedef  TYPE_2__ pdo_stmt_t ;
struct TYPE_7__ {TYPE_1__* cols; int /*<<< orphan*/  result; } ;
typedef  TYPE_3__ pdo_pgsql_stmt ;
struct TYPE_5__ {int pgsql_type; } ;

/* Variables and functions */
#define  BOOLOID 133 
#define  BYTEAOID 132 
#define  INT2OID 131 
#define  INT4OID 130 
#define  INT8OID 129 
#define  OIDOID 128 
 void* PDO_PARAM_BOOL ; 
 void* PDO_PARAM_INT ; 
 void* PDO_PARAM_LOB ; 
 void* PDO_PARAM_STR ; 
 void* PDO_PARAM_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQfmod (int /*<<< orphan*/ ,int) ; 
 char* PQfname (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PQfsize (int /*<<< orphan*/ ,int) ; 
 int PQftype (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 struct pdo_bound_param_data* zend_hash_find_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pdo_bound_param_data* zend_hash_index_find_ptr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zend_string_init (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pgsql_stmt_describe(pdo_stmt_t *stmt, int colno)
{
	pdo_pgsql_stmt *S = (pdo_pgsql_stmt*)stmt->driver_data;
	struct pdo_column_data *cols = stmt->columns;
	struct pdo_bound_param_data *param;
	char *str;

	if (!S->result) {
		return 0;
	}

	str = PQfname(S->result, colno);
	cols[colno].name = zend_string_init(str, strlen(str), 0);
	cols[colno].maxlen = PQfsize(S->result, colno);
	cols[colno].precision = PQfmod(S->result, colno);
	S->cols[colno].pgsql_type = PQftype(S->result, colno);

	switch (S->cols[colno].pgsql_type) {

		case BOOLOID:
			cols[colno].param_type = PDO_PARAM_BOOL;
			break;

		case OIDOID:
			/* did the user bind the column as a LOB ? */
			if (stmt->bound_columns && (
					(param = zend_hash_index_find_ptr(stmt->bound_columns, colno)) != NULL ||
					(param = zend_hash_find_ptr(stmt->bound_columns, cols[colno].name)) != NULL)) {

				if (PDO_PARAM_TYPE(param->param_type) == PDO_PARAM_LOB) {
					cols[colno].param_type = PDO_PARAM_LOB;
					break;
				}
			}
			cols[colno].param_type = PDO_PARAM_INT;
			break;

		case INT2OID:
		case INT4OID:
			cols[colno].param_type = PDO_PARAM_INT;
			break;

		case INT8OID:
			if (sizeof(zend_long)>=8) {
				cols[colno].param_type = PDO_PARAM_INT;
			} else {
				cols[colno].param_type = PDO_PARAM_STR;
			}
			break;

		case BYTEAOID:
			cols[colno].param_type = PDO_PARAM_LOB;
			break;

		default:
			cols[colno].param_type = PDO_PARAM_STR;
	}

	return 1;
}