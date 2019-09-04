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

__attribute__((used)) static int pdo_odbc_ucs22utf8(pdo_stmt_t *stmt, int is_unicode, const char *buf,
	zend_ulong buflen, zend_ulong *outlen)
{
#ifdef PHP_WIN32
	if (is_unicode && buflen) {
		pdo_odbc_stmt *S = (pdo_odbc_stmt*)stmt->driver_data;
		DWORD ret;

		ret = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)buf, buflen/sizeof(WCHAR), NULL, 0, NULL, NULL);
		if (ret == 0) {
			return PDO_ODBC_CONV_FAIL;
		}

		if (S->convbufsize <= ret) {
			S->convbufsize = ret + 1;
			S->convbuf = erealloc(S->convbuf, S->convbufsize);
		}

		ret = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)buf, buflen/sizeof(WCHAR), S->convbuf, S->convbufsize, NULL, NULL);
		if (ret == 0) {
			return PDO_ODBC_CONV_FAIL;
		}

		*outlen = ret;
		S->convbuf[*outlen] = '\0';
		return PDO_ODBC_CONV_OK;
	}
#endif
	return PDO_ODBC_CONV_NOT_REQUIRED;
}