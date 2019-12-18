#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  provInfo ;
typedef  int /*<<< orphan*/  WINECRYPT_CERTSTORE ;
struct TYPE_4__ {int cbSize; int /*<<< orphan*/  member_0; } ;
typedef  scalar_t__ (* PFN_CERT_DLL_OPEN_STORE_PROV_FUNC ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,void const*,int /*<<< orphan*/ *,TYPE_1__*) ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/  HCRYPTPROV ;
typedef  int /*<<< orphan*/ * HCRYPTOIDFUNCSET ;
typedef  int /*<<< orphan*/  HCRYPTOIDFUNCADDR ;
typedef  int /*<<< orphan*/ * HCERTSTORE ;
typedef  int DWORD ;
typedef  TYPE_1__ CERT_STORE_PROV_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  CERT_STORE_CREATE_NEW_FLAG ; 
 int CERT_STORE_DELETE_FLAG ; 
 int /*<<< orphan*/  CERT_STORE_PROV_MEMORY ; 
 int /*<<< orphan*/  CRYPT_OID_OPEN_STORE_PROV_FUNC ; 
 int /*<<< orphan*/ * CRYPT_ProvCreateStore (int,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  CertCloseStore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CertOpenStore (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CryptFreeOIDFunctionAddress (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CryptGetOIDFunctionAddress (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CryptInitOIDFunctionSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_FILE_NOT_FOUND ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 

WINECRYPT_CERTSTORE *CRYPT_ProvOpenStore(LPCSTR lpszStoreProvider,
 DWORD dwEncodingType, HCRYPTPROV hCryptProv, DWORD dwFlags, const void *pvPara)
{
    static HCRYPTOIDFUNCSET set = NULL;
    PFN_CERT_DLL_OPEN_STORE_PROV_FUNC provOpenFunc;
    HCRYPTOIDFUNCADDR hFunc;
    WINECRYPT_CERTSTORE *ret = NULL;

    if (!set)
        set = CryptInitOIDFunctionSet(CRYPT_OID_OPEN_STORE_PROV_FUNC, 0);
    CryptGetOIDFunctionAddress(set, dwEncodingType, lpszStoreProvider, 0,
     (void **)&provOpenFunc, &hFunc);
    if (provOpenFunc)
    {
        CERT_STORE_PROV_INFO provInfo = { 0 };

        provInfo.cbSize = sizeof(provInfo);
        if (dwFlags & CERT_STORE_DELETE_FLAG)
            provOpenFunc(lpszStoreProvider, dwEncodingType, hCryptProv,
             dwFlags, pvPara, NULL, &provInfo);
        else
        {
            HCERTSTORE memStore;

            memStore = CertOpenStore(CERT_STORE_PROV_MEMORY, 0, 0,
             CERT_STORE_CREATE_NEW_FLAG, NULL);
            if (memStore)
            {
                if (provOpenFunc(lpszStoreProvider, dwEncodingType, hCryptProv,
                 dwFlags, pvPara, memStore, &provInfo))
                    ret = CRYPT_ProvCreateStore(dwFlags, memStore, &provInfo);
                else
                    CertCloseStore(memStore, 0);
            }
        }
        CryptFreeOIDFunctionAddress(hFunc, 0);
    }
    else
        SetLastError(ERROR_FILE_NOT_FOUND);
    return ret;
}