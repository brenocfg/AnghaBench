#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_ulong ;
struct TYPE_9__ {int /*<<< orphan*/  supports_placeholders; int /*<<< orphan*/  error_code; int /*<<< orphan*/ * methods; TYPE_2__* driver_data; } ;
typedef  TYPE_1__ pdo_stmt_t ;
struct TYPE_10__ {int num_params; int /*<<< orphan*/  max_length; void* in_length; void* in_null; int /*<<< orphan*/ * params; scalar_t__ params_given; int /*<<< orphan*/  stmt; TYPE_3__* H; } ;
typedef  TYPE_2__ pdo_mysql_stmt ;
struct TYPE_11__ {int /*<<< orphan*/  server; scalar_t__ emulate_prepare; } ;
typedef  TYPE_3__ pdo_mysql_db_handle ;
struct TYPE_12__ {int alloc_own_columns; int /*<<< orphan*/  error_code; scalar_t__ driver_data; } ;
typedef  TYPE_4__ pdo_dbh_t ;
typedef  int /*<<< orphan*/  my_bool ;
typedef  int /*<<< orphan*/  MYSQL_BIND ;

/* Variables and functions */
 int /*<<< orphan*/  PDO_ATTR_MAX_COLUMN_LEN ; 
 int /*<<< orphan*/  PDO_DBG_ENTER (char*) ; 
 int /*<<< orphan*/  PDO_DBG_INF_FMT (char*,...) ; 
 int /*<<< orphan*/  PDO_DBG_RETURN (int) ; 
 int /*<<< orphan*/  PDO_PLACEHOLDER_NONE ; 
 int /*<<< orphan*/  PDO_PLACEHOLDER_POSITIONAL ; 
 void* ecalloc (int,int) ; 
 int /*<<< orphan*/  efree (char*) ; 
 int mysql_errno (int /*<<< orphan*/ ) ; 
 int mysql_get_server_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mysql_stmt_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mysql_stmt_methods ; 
 int mysql_stmt_param_count (int /*<<< orphan*/ ) ; 
 scalar_t__ mysql_stmt_prepare (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  pdo_attr_lval (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdo_mysql_error (TYPE_4__*) ; 
 int pdo_parse_params (TYPE_1__*,char*,size_t,char**,size_t*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mysql_handle_preparer(pdo_dbh_t *dbh, const char *sql, size_t sql_len, pdo_stmt_t *stmt, zval *driver_options)
{
	pdo_mysql_db_handle *H = (pdo_mysql_db_handle *)dbh->driver_data;
	pdo_mysql_stmt *S = ecalloc(1, sizeof(pdo_mysql_stmt));
	char *nsql = NULL;
	size_t nsql_len = 0;
	int ret;
	int server_version;

	PDO_DBG_ENTER("mysql_handle_preparer");
	PDO_DBG_INF_FMT("dbh=%p", dbh);
	PDO_DBG_INF_FMT("sql=%.*s", (int)sql_len, sql);

	S->H = H;
	stmt->driver_data = S;
	stmt->methods = &mysql_stmt_methods;

	if (H->emulate_prepare) {
		goto end;
	}

	server_version = mysql_get_server_version(H->server);
	if (server_version < 40100) {
		goto fallback;
	}
	stmt->supports_placeholders = PDO_PLACEHOLDER_POSITIONAL;
	ret = pdo_parse_params(stmt, (char*)sql, sql_len, &nsql, &nsql_len);

	if (ret == 1) {
		/* query was rewritten */
		sql = nsql;
		sql_len = nsql_len;
	} else if (ret == -1) {
		/* failed to parse */
		strcpy(dbh->error_code, stmt->error_code);
		PDO_DBG_RETURN(0);
	}

	if (!(S->stmt = mysql_stmt_init(H->server))) {
		pdo_mysql_error(dbh);
		if (nsql) {
			efree(nsql);
		}
		PDO_DBG_RETURN(0);
	}

	if (mysql_stmt_prepare(S->stmt, sql, sql_len)) {
		/* TODO: might need to pull statement specific info here? */
		/* if the query isn't supported by the protocol, fallback to emulation */
		if (mysql_errno(H->server) == 1295) {
			if (nsql) {
				efree(nsql);
			}
			goto fallback;
		}
		pdo_mysql_error(dbh);
		if (nsql) {
			efree(nsql);
		}
		PDO_DBG_RETURN(0);
	}
	if (nsql) {
		efree(nsql);
	}

	S->num_params = mysql_stmt_param_count(S->stmt);

	if (S->num_params) {
		S->params_given = 0;
#if defined(PDO_USE_MYSQLND)
		S->params = NULL;
#else
		S->params = ecalloc(S->num_params, sizeof(MYSQL_BIND));
		S->in_null = ecalloc(S->num_params, sizeof(my_bool));
		S->in_length = ecalloc(S->num_params, sizeof(zend_ulong));
#endif
	}
	dbh->alloc_own_columns = 1;

	S->max_length = pdo_attr_lval(driver_options, PDO_ATTR_MAX_COLUMN_LEN, 0);

	PDO_DBG_RETURN(1);

fallback:
end:
	stmt->supports_placeholders = PDO_PLACEHOLDER_NONE;

	PDO_DBG_RETURN(1);
}