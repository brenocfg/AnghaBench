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
typedef  int /*<<< orphan*/  zend_string ;
typedef  int zend_long ;
typedef  int /*<<< orphan*/  ub4 ;
struct TYPE_4__ {void* last_err; int /*<<< orphan*/  err; int /*<<< orphan*/  svc; int /*<<< orphan*/  session; int /*<<< orphan*/  prefetch; } ;
typedef  TYPE_1__ pdo_oci_db_handle ;
struct TYPE_5__ {int auto_commit; int /*<<< orphan*/  in_txn; scalar_t__ driver_data; } ;
typedef  TYPE_2__ pdo_dbh_t ;
typedef  int /*<<< orphan*/  dvoid ;

/* Variables and functions */
 void* OCIAttrSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* OCITransCommit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OCI_ATTR_ACTION ; 
 int /*<<< orphan*/  OCI_ATTR_CALL_TIMEOUT ; 
 int /*<<< orphan*/  OCI_ATTR_CLIENT_IDENTIFIER ; 
 int /*<<< orphan*/  OCI_ATTR_CLIENT_INFO ; 
 int /*<<< orphan*/  OCI_ATTR_MODULE ; 
 int /*<<< orphan*/  OCI_HTYPE_SESSION ; 
 int /*<<< orphan*/  OCI_HTYPE_SVCCTX ; 
#define  PDO_ATTR_AUTOCOMMIT 134 
#define  PDO_ATTR_PREFETCH 133 
#define  PDO_OCI_ATTR_ACTION 132 
#define  PDO_OCI_ATTR_CALL_TIMEOUT 131 
#define  PDO_OCI_ATTR_CLIENT_IDENTIFIER 130 
#define  PDO_OCI_ATTR_CLIENT_INFO 129 
#define  PDO_OCI_ATTR_MODULE 128 
 int /*<<< orphan*/  UNEXPECTED (int) ; 
 int /*<<< orphan*/  ZSTR_LEN (int /*<<< orphan*/ *) ; 
 scalar_t__ ZSTR_VAL (int /*<<< orphan*/ *) ; 
 void* oci_drv_error (char*) ; 
 int /*<<< orphan*/  pdo_oci_sanitize_prefetch (int) ; 
 int zval_get_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zval_try_get_string (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int oci_handle_set_attribute(pdo_dbh_t *dbh, zend_long attr, zval *val) /* {{{ */
{
	zend_long lval = zval_get_long(val);
	pdo_oci_db_handle *H = (pdo_oci_db_handle *)dbh->driver_data;

	switch (attr) {
		case PDO_ATTR_AUTOCOMMIT:
		{
			if (dbh->in_txn) {
				/* Assume they want to commit whatever is outstanding */
				H->last_err = OCITransCommit(H->svc, H->err, 0);

				if (H->last_err) {
					H->last_err = oci_drv_error("OCITransCommit");
					return 0;
				}
				dbh->in_txn = 0;
			}

			dbh->auto_commit = (unsigned int)lval? 1 : 0;
			return 1;
		}
		case PDO_ATTR_PREFETCH:
		{
			H->prefetch = pdo_oci_sanitize_prefetch(lval);
			return 1;
		}
		case PDO_OCI_ATTR_ACTION:
		{
#if (OCI_MAJOR_VERSION >= 10)
			zend_string *action = zval_try_get_string(val);
			if (UNEXPECTED(!action)) {
				return 0;
			}

			H->last_err = OCIAttrSet(H->session, OCI_HTYPE_SESSION,
				(dvoid *) ZSTR_VAL(action), (ub4) ZSTR_LEN(action),
				OCI_ATTR_ACTION, H->err);
			if (H->last_err) {
				oci_drv_error("OCIAttrSet: OCI_ATTR_ACTION");
				return 0;
			}
			return 1;
#else
			oci_drv_error("Unsupported attribute type");
			return 0;
#endif
		}
		case PDO_OCI_ATTR_CLIENT_INFO:
		{
#if (OCI_MAJOR_VERSION >= 10)
			zend_string *client_info = zval_try_get_string(val);
			if (UNEXPECTED(!client_info)) {
				return 0;
			}

			H->last_err = OCIAttrSet(H->session, OCI_HTYPE_SESSION,
				(dvoid *) ZSTR_VAL(client_info), (ub4) ZSTR_LEN(client_info),
				OCI_ATTR_CLIENT_INFO, H->err);
			if (H->last_err) {
				oci_drv_error("OCIAttrSet: OCI_ATTR_CLIENT_INFO");
				return 0;
			}
			return 1;
#else
			oci_drv_error("Unsupported attribute type");
			return 0;
#endif
		}
		case PDO_OCI_ATTR_CLIENT_IDENTIFIER:
		{
#if (OCI_MAJOR_VERSION >= 10)
			zend_string *identifier = zval_try_get_string(val);
			if (UNEXPECTED(!identifier)) {
				return 0;
			}

			H->last_err = OCIAttrSet(H->session, OCI_HTYPE_SESSION,
				(dvoid *) ZSTR_VAL(identifier), (ub4) ZSTR_LEN(identifier),
				OCI_ATTR_CLIENT_IDENTIFIER, H->err);
			if (H->last_err) {
				oci_drv_error("OCIAttrSet: OCI_ATTR_CLIENT_IDENTIFIER");
				return 0;
			}
			return 1;
#else
			oci_drv_error("Unsupported attribute type");
			return 0;
#endif
		}
		case PDO_OCI_ATTR_MODULE:
		{
#if (OCI_MAJOR_VERSION >= 10)
			zend_string *module = zval_try_get_string(val);
			if (UNEXPECTED(!module)) {
				return 0;
			}

			H->last_err = OCIAttrSet(H->session, OCI_HTYPE_SESSION,
				(dvoid *) ZSTR_VAL(module), (ub4) ZSTR_LEN(module),
				OCI_ATTR_MODULE, H->err);
			if (H->last_err) {
				oci_drv_error("OCIAttrSet: OCI_ATTR_MODULE");
				return 0;
			}
			return 1;
#else
			oci_drv_error("Unsupported attribute type");
			return 0;
#endif
		}
		case PDO_OCI_ATTR_CALL_TIMEOUT:
		{
#if (OCI_MAJOR_VERSION >= 18)
			ub4 timeout = (ub4) lval;

			H->last_err = OCIAttrSet(H->svc, OCI_HTYPE_SVCCTX,
				(dvoid *) &timeout, (ub4) 0,
				OCI_ATTR_CALL_TIMEOUT, H->err);
			if (H->last_err) {
				oci_drv_error("OCIAttrSet: OCI_ATTR_CALL_TIMEOUT");
				return 0;
			}
			return 1;
#else
			oci_drv_error("Unsupported attribute type");
			return 0;
#endif
		}
		default:
			return 0;
	}

}