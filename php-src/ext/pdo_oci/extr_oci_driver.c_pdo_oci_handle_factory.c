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
typedef  int /*<<< orphan*/  ub4 ;
typedef  int /*<<< orphan*/  text ;
struct pdo_data_src_parser {char* member_0; char* member_1; void* optval; scalar_t__ freeme; int /*<<< orphan*/  member_2; } ;
typedef  int /*<<< orphan*/  sb4 ;
struct TYPE_6__ {int attached; void* last_err; int /*<<< orphan*/  max_char_width; int /*<<< orphan*/  err; int /*<<< orphan*/ * env; void* session; void* svc; void* server; int /*<<< orphan*/  charset; int /*<<< orphan*/  prefetch; } ;
typedef  TYPE_1__ pdo_oci_db_handle ;
struct TYPE_7__ {int alloc_own_columns; int /*<<< orphan*/  native_case; int /*<<< orphan*/ * methods; void* password; int /*<<< orphan*/  is_persistent; void* username; TYPE_1__* driver_data; int /*<<< orphan*/  data_source_len; int /*<<< orphan*/  data_source; } ;
typedef  TYPE_2__ pdo_dbh_t ;
typedef  int /*<<< orphan*/  oratext ;
typedef  int /*<<< orphan*/  dvoid ;

/* Variables and functions */
 void* OCIAttrSet (void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ OCIEnvNlsCreate (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* OCIHandleAlloc (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OCINlsCharSetNameToId (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 void* OCINlsNumericInfoGet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* OCIServerAttach (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* OCISessionBegin (void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OCI_ATTR_PASSWORD ; 
 int /*<<< orphan*/  OCI_ATTR_SERVER ; 
 int /*<<< orphan*/  OCI_ATTR_SESSION ; 
 int /*<<< orphan*/  OCI_ATTR_USERNAME ; 
 int /*<<< orphan*/  OCI_CRED_RDBMS ; 
 int /*<<< orphan*/  OCI_DEFAULT ; 
 int /*<<< orphan*/  OCI_HTYPE_ERROR ; 
 int /*<<< orphan*/  OCI_HTYPE_SERVER ; 
 int /*<<< orphan*/  OCI_HTYPE_SESSION ; 
 int /*<<< orphan*/  OCI_HTYPE_SVCCTX ; 
 int /*<<< orphan*/  OCI_NLS_CHARSET_MAXBYTESZ ; 
 scalar_t__ OCI_SUCCESS ; 
 int /*<<< orphan*/  PDO_CASE_UPPER ; 
 int /*<<< orphan*/  PDO_OCI_INIT_MODE ; 
 int /*<<< orphan*/  PDO_OCI_PREFETCH_DEFAULT ; 
 int /*<<< orphan*/  efree (void*) ; 
 int /*<<< orphan*/  oci_drv_error (char*) ; 
 int /*<<< orphan*/  oci_handle_closer (TYPE_2__*) ; 
 int /*<<< orphan*/  oci_init_error (char*) ; 
 int /*<<< orphan*/  oci_methods ; 
 int /*<<< orphan*/ * pdo_oci_Env ; 
 TYPE_1__* pecalloc (int,int,int /*<<< orphan*/ ) ; 
 void* pestrdup (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_pdo_parse_data_source (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pdo_data_src_parser*,int) ; 
 scalar_t__ strlen (void*) ; 

__attribute__((used)) static int pdo_oci_handle_factory(pdo_dbh_t *dbh, zval *driver_options) /* {{{ */
{
	pdo_oci_db_handle *H;
	int i, ret = 0;
	struct pdo_data_src_parser vars[] = {
		{ "charset",  NULL,	0 },
		{ "dbname",   "",	0 },
		{ "user",     NULL, 0 },
		{ "password", NULL, 0 }
	};

	php_pdo_parse_data_source(dbh->data_source, dbh->data_source_len, vars, 4);

	H = pecalloc(1, sizeof(*H), dbh->is_persistent);
	dbh->driver_data = H;

	H->prefetch = PDO_OCI_PREFETCH_DEFAULT;

	/* allocate an environment */
#if HAVE_OCIENVNLSCREATE
	if (vars[0].optval) {
		H->charset = OCINlsCharSetNameToId(pdo_oci_Env, (const oratext *)vars[0].optval);
		if (!H->charset) {
			oci_init_error("OCINlsCharSetNameToId: unknown character set name");
			goto cleanup;
		} else {
			if (OCIEnvNlsCreate(&H->env, PDO_OCI_INIT_MODE, 0, NULL, NULL, NULL, 0, NULL, H->charset, H->charset) != OCI_SUCCESS) {
				oci_init_error("OCIEnvNlsCreate: Check the character set is valid and that PHP has access to Oracle libraries and NLS data");
				goto cleanup;
			}
		}
	}
#endif
	if (H->env == NULL) {
		/* use the global environment */
		H->env = pdo_oci_Env;
	}

	/* something to hold errors */
	OCIHandleAlloc(H->env, (dvoid **)&H->err, OCI_HTYPE_ERROR, 0, NULL);

	/* handle for the server */
	OCIHandleAlloc(H->env, (dvoid **)&H->server, OCI_HTYPE_SERVER, 0, NULL);

	H->last_err = OCIServerAttach(H->server, H->err, (text*)vars[1].optval,
		   	(sb4) strlen(vars[1].optval), OCI_DEFAULT);

	if (H->last_err) {
		oci_drv_error("pdo_oci_handle_factory");
		goto cleanup;
	}

	H->attached = 1;

	/* create a service context */
	H->last_err = OCIHandleAlloc(H->env, (dvoid**)&H->svc, OCI_HTYPE_SVCCTX, 0, NULL);
	if (H->last_err) {
		oci_drv_error("OCIHandleAlloc: OCI_HTYPE_SVCCTX");
		goto cleanup;
	}

	H->last_err = OCIHandleAlloc(H->env, (dvoid**)&H->session, OCI_HTYPE_SESSION, 0, NULL);
	if (H->last_err) {
		oci_drv_error("OCIHandleAlloc: OCI_HTYPE_SESSION");
		goto cleanup;
	}

	/* set server handle into service handle */
	H->last_err = OCIAttrSet(H->svc, OCI_HTYPE_SVCCTX, H->server, 0, OCI_ATTR_SERVER, H->err);
	if (H->last_err) {
		oci_drv_error("OCIAttrSet: OCI_ATTR_SERVER");
		goto cleanup;
	}

	/* username */
	if (!dbh->username && vars[2].optval) {
		dbh->username = pestrdup(vars[2].optval, dbh->is_persistent);
	}

	if (dbh->username) {
		H->last_err = OCIAttrSet(H->session, OCI_HTYPE_SESSION,
			   	dbh->username, (ub4) strlen(dbh->username),
				OCI_ATTR_USERNAME, H->err);
		if (H->last_err) {
			oci_drv_error("OCIAttrSet: OCI_ATTR_USERNAME");
			goto cleanup;
		}
	}

	/* password */
	if (!dbh->password && vars[3].optval) {
		dbh->password = pestrdup(vars[3].optval, dbh->is_persistent);
	}

	if (dbh->password) {
		H->last_err = OCIAttrSet(H->session, OCI_HTYPE_SESSION,
			   	dbh->password, (ub4) strlen(dbh->password),
				OCI_ATTR_PASSWORD, H->err);
		if (H->last_err) {
			oci_drv_error("OCIAttrSet: OCI_ATTR_PASSWORD");
			goto cleanup;
		}
	}

	/* Now fire up the session */
	H->last_err = OCISessionBegin(H->svc, H->err, H->session, OCI_CRED_RDBMS, OCI_DEFAULT);
	if (H->last_err) {
		oci_drv_error("OCISessionBegin");
		goto cleanup;
	}

	/* set the server handle into service handle */
	H->last_err = OCIAttrSet(H->svc, OCI_HTYPE_SVCCTX, H->session, 0, OCI_ATTR_SESSION, H->err);
	if (H->last_err) {
		oci_drv_error("OCIAttrSet: OCI_ATTR_SESSION");
		goto cleanup;
	}

	/* Get max character width */
 	H->last_err = OCINlsNumericInfoGet(H->env, H->err, &H->max_char_width, OCI_NLS_CHARSET_MAXBYTESZ);
 	if (H->last_err) {
 		oci_drv_error("OCINlsNumericInfoGet: OCI_NLS_CHARSET_MAXBYTESZ");
 		goto cleanup;
 	}

	dbh->methods = &oci_methods;
	dbh->alloc_own_columns = 1;
	dbh->native_case = PDO_CASE_UPPER;

	ret = 1;

cleanup:
	for (i = 0; i < sizeof(vars)/sizeof(vars[0]); i++) {
		if (vars[i].freeme) {
			efree(vars[i].optval);
		}
	}

	if (!ret) {
		oci_handle_closer(dbh);
	}

	return ret;
}