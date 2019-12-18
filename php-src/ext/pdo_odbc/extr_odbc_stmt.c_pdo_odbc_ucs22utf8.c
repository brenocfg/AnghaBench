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
struct TYPE_5__ {scalar_t__ convbufsize; char* convbuf; } ;
typedef  TYPE_2__ pdo_odbc_stmt ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 int PDO_ODBC_CONV_FAIL ; 
 int PDO_ODBC_CONV_NOT_REQUIRED ; 
 int PDO_ODBC_CONV_OK ; 
 scalar_t__ WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* erealloc (char*,scalar_t__) ; 

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