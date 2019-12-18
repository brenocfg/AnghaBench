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
typedef  int /*<<< orphan*/  zend_long ;
typedef  int /*<<< orphan*/  zend_bool ;
struct pdo_column_data {int param_type; } ;
struct TYPE_8__ {int /*<<< orphan*/  database_object_handle; struct pdo_column_data* columns; scalar_t__ driver_data; } ;
typedef  TYPE_3__ pdo_stmt_t ;
struct TYPE_9__ {TYPE_2__* H; TYPE_1__* cols; scalar_t__ current_row; int /*<<< orphan*/  result; } ;
typedef  TYPE_4__ pdo_pgsql_stmt ;
struct TYPE_7__ {int /*<<< orphan*/  server; } ;
struct TYPE_6__ {int boolval; int /*<<< orphan*/  pgsql_type; int /*<<< orphan*/  intval; } ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  INV_READ ; 
 int /*<<< orphan*/  OIDOID ; 
#define  PDO_PARAM_BOOL 135 
#define  PDO_PARAM_INPUT_OUTPUT 134 
#define  PDO_PARAM_INT 133 
#define  PDO_PARAM_LOB 132 
#define  PDO_PARAM_NULL 131 
#define  PDO_PARAM_STMT 130 
#define  PDO_PARAM_STR 129 
#define  PDO_PARAM_ZVAL 128 
 int /*<<< orphan*/  PQfreemem (char*) ; 
 scalar_t__ PQgetisnull (int /*<<< orphan*/ ,scalar_t__,int) ; 
 size_t PQgetlength (int /*<<< orphan*/ ,scalar_t__,int) ; 
 char* PQgetvalue (int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ PQunescapeBytea (unsigned char*,size_t*) ; 
 int /*<<< orphan*/  TEMP_STREAM_READONLY ; 
 int /*<<< orphan*/  ZEND_ATOL (int /*<<< orphan*/ ,char*) ; 
 char* estrndup (char*,size_t) ; 
 int lo_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pdo_pgsql_create_lob_stream (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ php_stream_memory_open (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strtoul (char*,char**,int) ; 

__attribute__((used)) static int pgsql_stmt_get_col(pdo_stmt_t *stmt, int colno, char **ptr, size_t *len, int *caller_frees )
{
	pdo_pgsql_stmt *S = (pdo_pgsql_stmt*)stmt->driver_data;
	struct pdo_column_data *cols = stmt->columns;
	size_t tmp_len;

	if (!S->result) {
		return 0;
	}

	/* We have already increased count by 1 in pgsql_stmt_fetch() */
	if (PQgetisnull(S->result, S->current_row - 1, colno)) { /* Check if we got NULL */
		*ptr = NULL;
		*len = 0;
	} else {
		*ptr = PQgetvalue(S->result, S->current_row - 1, colno);
		*len = PQgetlength(S->result, S->current_row - 1, colno);

		switch (cols[colno].param_type) {

			case PDO_PARAM_INT:
				ZEND_ATOL(S->cols[colno].intval, *ptr);
				*ptr = (char *) &(S->cols[colno].intval);
				*len = sizeof(zend_long);
				break;

			case PDO_PARAM_BOOL:
				S->cols[colno].boolval = **ptr == 't';
				*ptr = (char *) &(S->cols[colno].boolval);
				*len = sizeof(zend_bool);
				break;

			case PDO_PARAM_LOB:
				if (S->cols[colno].pgsql_type == OIDOID) {
					/* ooo, a real large object */
					char *end_ptr;
					Oid oid = (Oid)strtoul(*ptr, &end_ptr, 10);
					int loid = lo_open(S->H->server, oid, INV_READ);
					if (loid >= 0) {
						*ptr = (char*)pdo_pgsql_create_lob_stream(&stmt->database_object_handle, loid, oid);
						*len = 0;
						return *ptr ? 1 : 0;
					}
					*ptr = NULL;
					*len = 0;
					return 0;
				} else {
					char *tmp_ptr = (char *)PQunescapeBytea((unsigned char *)*ptr, &tmp_len);
					if (!tmp_ptr) {
						/* PQunescapeBytea returned an error */
						*len = 0;
						return 0;
					}
					if (!tmp_len) {
						/* Empty string, return as empty stream */
						*ptr = (char *)php_stream_memory_open(TEMP_STREAM_READONLY, "", 0);
						PQfreemem(tmp_ptr);
						*len = 0;
					} else {
						*ptr = estrndup(tmp_ptr, tmp_len);
						PQfreemem(tmp_ptr);
						*len = tmp_len;
						*caller_frees = 1;
					}
				}
				break;
			case PDO_PARAM_NULL:
			case PDO_PARAM_STR:
			case PDO_PARAM_STMT:
			case PDO_PARAM_INPUT_OUTPUT:
			case PDO_PARAM_ZVAL:
			default:
				break;
		}
	}

	return 1;
}