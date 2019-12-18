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
typedef  int /*<<< orphan*/  WINECRYPT_CERTSTORE ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/  HCRYPTPROV ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/ * CRYPT_SysOpenStoreW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CryptMemAlloc (int) ; 
 int /*<<< orphan*/  CryptMemFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR_FILE_NOT_FOUND ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_a (void const*) ; 

__attribute__((used)) static WINECRYPT_CERTSTORE *CRYPT_SysOpenStoreA(HCRYPTPROV hCryptProv,
 DWORD dwFlags, const void *pvPara)
{
    int len;
    WINECRYPT_CERTSTORE *ret = NULL;

    TRACE("(%ld, %08x, %s)\n", hCryptProv, dwFlags,
     debugstr_a(pvPara));

    if (!pvPara)
    {
        SetLastError(ERROR_FILE_NOT_FOUND);
        return NULL;
    }
    len = MultiByteToWideChar(CP_ACP, 0, pvPara, -1, NULL, 0);
    if (len)
    {
        LPWSTR storeName = CryptMemAlloc(len * sizeof(WCHAR));

        if (storeName)
        {
            MultiByteToWideChar(CP_ACP, 0, pvPara, -1, storeName, len);
            ret = CRYPT_SysOpenStoreW(hCryptProv, dwFlags, storeName);
            CryptMemFree(storeName);
        }
    }
    return ret;
}