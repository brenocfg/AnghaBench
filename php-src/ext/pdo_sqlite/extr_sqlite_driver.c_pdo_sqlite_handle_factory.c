#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int zend_long ;
struct TYPE_7__ {int /*<<< orphan*/ * errmsg; scalar_t__ errcode; } ;
struct TYPE_8__ {int /*<<< orphan*/  db; TYPE_1__ einfo; } ;
typedef  TYPE_2__ pdo_sqlite_db_handle ;
struct TYPE_9__ {int alloc_own_columns; int max_escaped_char_length; int /*<<< orphan*/ * methods; int /*<<< orphan*/  data_source; TYPE_2__* driver_data; int /*<<< orphan*/  is_persistent; } ;
typedef  TYPE_3__ pdo_dbh_t ;

/* Variables and functions */
 int /*<<< orphan*/  PDO_ATTR_TIMEOUT ; 
 int /*<<< orphan*/  PDO_SQLITE_ATTR_OPEN_FLAGS ; 
 scalar_t__* PG (int /*<<< orphan*/ ) ; 
 int SQLITE_OK ; 
 int SQLITE_OPEN_CREATE ; 
 int SQLITE_OPEN_READWRITE ; 
 int /*<<< orphan*/  authorizer ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* make_filename_safe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_basedir ; 
 int pdo_attr_lval (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pdo_sqlite_error (TYPE_3__*) ; 
 TYPE_2__* pecalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_pdo_get_exception () ; 
 int /*<<< orphan*/  sqlite3_busy_timeout (int /*<<< orphan*/ ,int) ; 
 int sqlite3_open_v2 (char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_set_authorizer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite_methods ; 
 int /*<<< orphan*/  zend_throw_exception_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pdo_sqlite_handle_factory(pdo_dbh_t *dbh, zval *driver_options) /* {{{ */
{
	pdo_sqlite_db_handle *H;
	int i, ret = 0;
	zend_long timeout = 60, flags;
	char *filename;

	H = pecalloc(1, sizeof(pdo_sqlite_db_handle), dbh->is_persistent);

	H->einfo.errcode = 0;
	H->einfo.errmsg = NULL;
	dbh->driver_data = H;

	filename = make_filename_safe(dbh->data_source);

	if (!filename) {
		zend_throw_exception_ex(php_pdo_get_exception(), 0,
			"open_basedir prohibits opening %s",
			dbh->data_source);
		goto cleanup;
	}

	flags = pdo_attr_lval(driver_options, PDO_SQLITE_ATTR_OPEN_FLAGS, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);

	i = sqlite3_open_v2(filename, &H->db, flags, NULL);

	efree(filename);

	if (i != SQLITE_OK) {
		pdo_sqlite_error(dbh);
		goto cleanup;
	}

	if (PG(open_basedir) && *PG(open_basedir)) {
		sqlite3_set_authorizer(H->db, authorizer, NULL);
	}

	if (driver_options) {
		timeout = pdo_attr_lval(driver_options, PDO_ATTR_TIMEOUT, timeout);
	}
	sqlite3_busy_timeout(H->db, timeout * 1000);

	dbh->alloc_own_columns = 1;
	dbh->max_escaped_char_length = 2;

	ret = 1;

cleanup:
	dbh->methods = &sqlite_methods;

	return ret;
}