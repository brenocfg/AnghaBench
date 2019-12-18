#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  vars ;
struct pdo_data_src_parser {char* member_0; char* member_1; char const* optval; scalar_t__ freeme; int /*<<< orphan*/  member_2; } ;
struct TYPE_6__ {int /*<<< orphan*/ * isc_status; int /*<<< orphan*/  db; int /*<<< orphan*/  sql_dialect; } ;
typedef  TYPE_1__ pdo_firebird_db_handle ;
struct TYPE_7__ {char const* username; char const* password; int alloc_own_columns; int /*<<< orphan*/ * methods; int /*<<< orphan*/  native_case; int /*<<< orphan*/  is_persistent; int /*<<< orphan*/  data_source_len; int /*<<< orphan*/  data_source; TYPE_1__* driver_data; } ;
typedef  TYPE_2__ pdo_dbh_t ;
typedef  int /*<<< orphan*/  errmsg ;
typedef  int /*<<< orphan*/  dpb_flags ;
typedef  int /*<<< orphan*/  ISC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  PDO_CASE_UPPER ; 
 int /*<<< orphan*/  PDO_FB_DIALECT ; 
 int /*<<< orphan*/  atoi (char const*) ; 
 int /*<<< orphan*/  efree (char const*) ; 
 int /*<<< orphan*/  fb_interpret (char*,int,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  firebird_handle_closer (TYPE_2__*) ; 
 int /*<<< orphan*/  firebird_methods ; 
 scalar_t__ isc_attach_database (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,short,char*) ; 
#define  isc_dpb_lc_ctype 131 
#define  isc_dpb_password 130 
#define  isc_dpb_sql_role_name 129 
#define  isc_dpb_user_name 128 
 char isc_dpb_version1 ; 
 TYPE_1__* pecalloc (int,int,int /*<<< orphan*/ ) ; 
 void* pestrdup (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_pdo_get_exception () ; 
 int /*<<< orphan*/  php_pdo_parse_data_source (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pdo_data_src_parser*,int) ; 
 short slprintf (char*,short,char*,char const,unsigned char,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  zend_throw_exception_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int pdo_firebird_handle_factory(pdo_dbh_t *dbh, zval *driver_options) /* {{{ */
{
	struct pdo_data_src_parser vars[] = {
		{ "dbname", NULL, 0 },
		{ "charset",  NULL,	0 },
		{ "role", NULL,	0 },
		{ "dialect", "3", 0 },
		{ "user", NULL, 0 },
		{ "password", NULL, 0 }
	};
	int i, ret = 0;
	short buf_len = 256, dpb_len;

	pdo_firebird_db_handle *H = dbh->driver_data = pecalloc(1,sizeof(*H),dbh->is_persistent);

	php_pdo_parse_data_source(dbh->data_source, dbh->data_source_len, vars, 6);

	if (!dbh->username && vars[4].optval) {
		dbh->username = pestrdup(vars[4].optval, dbh->is_persistent);
	}

	if (!dbh->password && vars[5].optval) {
		dbh->password = pestrdup(vars[5].optval, dbh->is_persistent);
	}

	do {
		static char const dpb_flags[] = {
			isc_dpb_user_name, isc_dpb_password, isc_dpb_lc_ctype, isc_dpb_sql_role_name };
		char const *dpb_values[] = { dbh->username, dbh->password, vars[1].optval, vars[2].optval };
		char dpb_buffer[256] = { isc_dpb_version1 }, *dpb;

		dpb = dpb_buffer + 1;

		/* loop through all the provided arguments and set dpb fields accordingly */
		for (i = 0; i < sizeof(dpb_flags); ++i) {
			if (dpb_values[i] && buf_len > 0) {
				dpb_len = slprintf(dpb, buf_len, "%c%c%s", dpb_flags[i], (unsigned char)strlen(dpb_values[i]),
					dpb_values[i]);
				dpb += dpb_len;
				buf_len -= dpb_len;
			}
		}

		H->sql_dialect = PDO_FB_DIALECT;
		if (vars[3].optval) {
			H->sql_dialect = atoi(vars[3].optval);
		}

		/* fire it up baby! */
		if (isc_attach_database(H->isc_status, 0, vars[0].optval, &H->db,(short)(dpb-dpb_buffer), dpb_buffer)) {
			break;
		}

		dbh->methods = &firebird_methods;
		dbh->native_case = PDO_CASE_UPPER;
		dbh->alloc_own_columns = 1;

		ret = 1;

	} while (0);

	for (i = 0; i < sizeof(vars)/sizeof(vars[0]); ++i) {
		if (vars[i].freeme) {
			efree(vars[i].optval);
		}
	}

	if (!dbh->methods) {
		char errmsg[512];
		const ISC_STATUS *s = H->isc_status;
		fb_interpret(errmsg, sizeof(errmsg),&s);
		zend_throw_exception_ex(php_pdo_get_exception(), H->isc_status[1], "SQLSTATE[%s] [%d] %s",
				"HY000", H->isc_status[1], errmsg);
	}

	if (!ret) {
		firebird_handle_closer(dbh);
	}

	return ret;
}