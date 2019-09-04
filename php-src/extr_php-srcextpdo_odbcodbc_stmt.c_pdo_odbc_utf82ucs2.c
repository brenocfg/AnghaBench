#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zend_ulong ;
typedef  int /*<<< orphan*/  pdo_stmt_t ;

/* Variables and functions */
 int PDO_ODBC_CONV_NOT_REQUIRED ; 

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