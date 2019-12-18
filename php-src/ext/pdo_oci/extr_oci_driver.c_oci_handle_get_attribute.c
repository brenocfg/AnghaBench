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
typedef  int zend_long ;
typedef  int /*<<< orphan*/  verstr ;
typedef  int ub4 ;
typedef  int /*<<< orphan*/  ub1 ;
typedef  int /*<<< orphan*/  text ;
typedef  int sword ;
struct TYPE_4__ {int prefetch; int /*<<< orphan*/  last_err; int /*<<< orphan*/  err; int /*<<< orphan*/  svc; } ;
typedef  TYPE_1__ pdo_oci_db_handle ;
struct TYPE_5__ {int /*<<< orphan*/  auto_commit; scalar_t__ driver_data; } ;
typedef  TYPE_2__ pdo_dbh_t ;
typedef  int /*<<< orphan*/  infostr ;
typedef  int /*<<< orphan*/  dvoid ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  OCIAttrGet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OCIClientVersion (int*,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  OCIServerRelease (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  OCI_ATTR_CALL_TIMEOUT ; 
 int /*<<< orphan*/  OCI_HTYPE_SVCCTX ; 
#define  PDO_ATTR_AUTOCOMMIT 133 
#define  PDO_ATTR_CLIENT_VERSION 132 
#define  PDO_ATTR_PREFETCH 131 
#define  PDO_ATTR_SERVER_INFO 130 
#define  PDO_ATTR_SERVER_VERSION 129 
#define  PDO_OCI_ATTR_CALL_TIMEOUT 128 
 char* PHP_PDO_OCI_CLIENT_VERSION ; 
 int TRUE ; 
 int /*<<< orphan*/  ZVAL_BOOL (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ZVAL_STRING (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  oci_drv_error (char*) ; 
 int /*<<< orphan*/  slprintf (char*,int,char*,int,int,int,int,int) ; 

__attribute__((used)) static int oci_handle_get_attribute(pdo_dbh_t *dbh, zend_long attr, zval *return_value)  /* {{{ */
{
	pdo_oci_db_handle *H = (pdo_oci_db_handle *)dbh->driver_data;

	switch (attr) {
		case PDO_ATTR_SERVER_VERSION:
		case PDO_ATTR_SERVER_INFO:
		{
			text infostr[512];
			char verstr[15];
			ub4  vernum;

			if (OCIServerRelease(H->svc, H->err, infostr, (ub4)sizeof(infostr), (ub1)OCI_HTYPE_SVCCTX, &vernum))
			{
				ZVAL_STRING(return_value, "<<Unknown>>");
			} else {
				if (attr == PDO_ATTR_SERVER_INFO) {
					ZVAL_STRING(return_value, (char *)infostr);
				} else {
					slprintf(verstr, sizeof(verstr), "%d.%d.%d.%d.%d",
							 (int)((vernum>>24) & 0xFF),  /* version number */
							 (int)((vernum>>20) & 0x0F),  /* release number*/
							 (int)((vernum>>12) & 0xFF),  /* update number */
							 (int)((vernum>>8)  & 0x0F),  /* port release number */
							 (int)((vernum>>0)  & 0xFF)); /* port update number */

					ZVAL_STRING(return_value, verstr);
				}
			}
			return TRUE;
		}

		case PDO_ATTR_CLIENT_VERSION:
		{
#if OCI_MAJOR_VERSION > 10 || (OCI_MAJOR_VERSION == 10 && OCI_MINOR_VERSION >= 2)
			/* Run time client version */
			sword major, minor, update, patch, port_update;
			char verstr[15];

			OCIClientVersion(&major, &minor, &update, &patch, &port_update);
			slprintf(verstr, sizeof(verstr), "%d.%d.%d.%d.%d", major, minor, update, patch, port_update);
			ZVAL_STRING(return_value, verstr);
#elif defined(PHP_PDO_OCI_CLIENT_VERSION)
			/* Compile time client version */
			ZVAL_STRING(return_value, PHP_PDO_OCI_CLIENT_VERSION);
#else
			return FALSE;

#endif /* Check for OCIClientVersion() support */

			return TRUE;
		}

		case PDO_ATTR_AUTOCOMMIT:
			ZVAL_BOOL(return_value, dbh->auto_commit);
			return TRUE;

		case PDO_ATTR_PREFETCH:
			ZVAL_LONG(return_value, H->prefetch);
			return TRUE;
		case PDO_OCI_ATTR_CALL_TIMEOUT:
		{
#if (OCI_MAJOR_VERSION >= 18)
			ub4 timeout;

			H->last_err = OCIAttrGet(H->svc, OCI_HTYPE_SVCCTX,
				(dvoid *) &timeout, NULL,
				OCI_ATTR_CALL_TIMEOUT, H->err);
			if (H->last_err) {
				oci_drv_error("OCIAttrGet: OCI_ATTR_CALL_TIMEOUT");
				return FALSE;
			}

			ZVAL_LONG(return_value, (zend_long) timeout);
			return TRUE;
#else
			oci_drv_error("Unsupported attribute type");
			return FALSE;
#endif
		}
		default:
			return FALSE;

	}
	return FALSE;

}