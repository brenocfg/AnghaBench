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
typedef  int /*<<< orphan*/  zval ;
typedef  size_t zend_long ;
struct TYPE_8__ {size_t column_count; scalar_t__ driver_data; } ;
typedef  TYPE_3__ pdo_stmt_t ;
struct TYPE_9__ {TYPE_2__* H; TYPE_1__* cols; int /*<<< orphan*/  result; } ;
typedef  TYPE_4__ pdo_pgsql_stmt ;
struct TYPE_7__ {int /*<<< orphan*/  server; } ;
struct TYPE_6__ {int pgsql_type; } ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int Oid ;
typedef  int /*<<< orphan*/  ExecStatusType ;

/* Variables and functions */
 char* BOOLLABEL ; 
#define  BOOLOID 136 
 char* BYTEALABEL ; 
#define  BYTEAOID 135 
 char* DATELABEL ; 
#define  DATEOID 134 
 int FAILURE ; 
 char* INT2LABEL ; 
#define  INT2OID 133 
 char* INT4LABEL ; 
#define  INT4OID 132 
 char* INT8LABEL ; 
#define  INT8OID 131 
 int /*<<< orphan*/  PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQexec (int /*<<< orphan*/ ,char*) ; 
 int PQftable (int /*<<< orphan*/ ,size_t) ; 
 char* PQgetvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQresultStatus (int /*<<< orphan*/ *) ; 
 char* TEXTLABEL ; 
#define  TEXTOID 130 
 char* TIMESTAMPLABEL ; 
#define  TIMESTAMPOID 129 
 char* VARCHARLABEL ; 
#define  VARCHAROID 128 
 int /*<<< orphan*/  add_assoc_long (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  add_assoc_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* pdo_pgsql_translate_oid_to_table (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spprintf (char**,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int pgsql_stmt_get_column_meta(pdo_stmt_t *stmt, zend_long colno, zval *return_value)
{
	pdo_pgsql_stmt *S = (pdo_pgsql_stmt*)stmt->driver_data;
	PGresult *res;
	char *q=NULL;
	ExecStatusType status;
	Oid table_oid;
	char *table_name=NULL;

	if (!S->result) {
		return FAILURE;
	}

	if (colno >= stmt->column_count) {
		return FAILURE;
	}

	array_init(return_value);
	add_assoc_long(return_value, "pgsql:oid", S->cols[colno].pgsql_type);

	table_oid = PQftable(S->result, colno);
	add_assoc_long(return_value, "pgsql:table_oid", table_oid);
	table_name = pdo_pgsql_translate_oid_to_table(table_oid, S->H->server);
	if (table_name) {
		add_assoc_string(return_value, "table", table_name);
		efree(table_name);
	}

	switch (S->cols[colno].pgsql_type) {
		case BOOLOID:
			add_assoc_string(return_value, "native_type", BOOLLABEL);
			break;
		case BYTEAOID:
			add_assoc_string(return_value, "native_type", BYTEALABEL);
			break;
		case INT8OID:
			add_assoc_string(return_value, "native_type", INT8LABEL);
			break;
		case INT2OID:
			add_assoc_string(return_value, "native_type", INT2LABEL);
			break;
		case INT4OID:
			add_assoc_string(return_value, "native_type", INT4LABEL);
			break;
		case TEXTOID:
			add_assoc_string(return_value, "native_type", TEXTLABEL);
			break;
		case VARCHAROID:
			add_assoc_string(return_value, "native_type", VARCHARLABEL);
			break;
		case DATEOID:
			add_assoc_string(return_value, "native_type", DATELABEL);
			break;
		case TIMESTAMPOID:
			add_assoc_string(return_value, "native_type", TIMESTAMPLABEL);
			break;
		default:
			/* Fetch metadata from Postgres system catalogue */
			spprintf(&q, 0, "SELECT TYPNAME FROM PG_TYPE WHERE OID=%u", S->cols[colno].pgsql_type);
			res = PQexec(S->H->server, q);
			efree(q);
			status = PQresultStatus(res);
			if (status == PGRES_TUPLES_OK && 1 == PQntuples(res)) {
				add_assoc_string(return_value, "native_type", PQgetvalue(res, 0, 0));
			}
			PQclear(res);
	}
	return 1;
}