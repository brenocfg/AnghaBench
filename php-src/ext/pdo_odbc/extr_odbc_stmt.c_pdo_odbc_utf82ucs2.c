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
typedef  int zend_ulong ;
struct TYPE_4__ {scalar_t__ driver_data; } ;
typedef  TYPE_1__ pdo_stmt_t ;
struct TYPE_5__ {int convbufsize; scalar_t__ convbuf; } ;
typedef  TYPE_2__ pdo_odbc_stmt ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int) ; 
 int PDO_ODBC_CONV_FAIL ; 
 int PDO_ODBC_CONV_NOT_REQUIRED ; 
 int PDO_ODBC_CONV_OK ; 
 scalar_t__ erealloc (scalar_t__,int) ; 

__attribute__((used)) static int pdo_odbc_utf82ucs2(pdo_stmt_t *stmt, int is_unicode, const char *buf,
	zend_ulong buflen, zend_ulong *outlen)
{
#ifdef PHP_WIN32
	if (is_unicode && buflen) {
		pdo_odbc_stmt *S = (pdo_odbc_stmt*)stmt->driver_data;
		DWORD ret;

		ret = MultiByteToWideChar(CP_UTF8, 0, buf, buflen, NULL, 0);
		if (ret == 0) {
			/*printf("%s:%d %d [%d] %.*s\n", __FILE__, __LINE__, GetLastError(), buflen, buflen, buf);*/
			return PDO_ODBC_CONV_FAIL;
		}

		ret *= sizeof(WCHAR);

		if (S->convbufsize <= ret) {
			S->convbufsize = ret + sizeof(WCHAR);
			S->convbuf = erealloc(S->convbuf, S->convbufsize);
		}

		ret = MultiByteToWideChar(CP_UTF8, 0, buf, buflen, (LPWSTR)S->convbuf, S->convbufsize / sizeof(WCHAR));
		if (ret == 0) {
			/*printf("%s:%d %d [%d] %.*s\n", __FILE__, __LINE__, GetLastError(), buflen, buflen, buf);*/
			return PDO_ODBC_CONV_FAIL;
		}

		ret *= sizeof(WCHAR);
		*outlen = ret;
		return PDO_ODBC_CONV_OK;
	}
#endif
	return PDO_ODBC_CONV_NOT_REQUIRED;
}