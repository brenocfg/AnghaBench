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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  REGSAM ;
typedef  scalar_t__ LPWSTR ;
typedef  void const* LPCWSTR ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  HCRYPTPROV ;
typedef  int DWORD ;

/* Variables and functions */
 void* CERT_GROUP_POLICY_SYSTEM_STORE_REGPATH ; 
 void* CERT_LOCAL_MACHINE_SYSTEM_STORE_REGPATH ; 
 int CERT_STORE_CREATE_NEW_FLAG ; 
 int CERT_STORE_OPEN_EXISTING_FLAG ; 
 int CERT_STORE_READONLY_FLAG ; 
#define  CERT_SYSTEM_STORE_CURRENT_SERVICE 135 
#define  CERT_SYSTEM_STORE_CURRENT_USER 134 
#define  CERT_SYSTEM_STORE_CURRENT_USER_GROUP_POLICY 133 
#define  CERT_SYSTEM_STORE_LOCAL_MACHINE 132 
#define  CERT_SYSTEM_STORE_LOCAL_MACHINE_ENTERPRISE 131 
#define  CERT_SYSTEM_STORE_LOCAL_MACHINE_GROUP_POLICY 130 
 int CERT_SYSTEM_STORE_LOCATION_MASK ; 
#define  CERT_SYSTEM_STORE_SERVICES 129 
#define  CERT_SYSTEM_STORE_USERS 128 
 int /*<<< orphan*/  CRYPT_ImportSystemRootCertsToReg () ; 
 int /*<<< orphan*/ * CRYPT_RegOpenStore (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ CryptMemAlloc (int) ; 
 int /*<<< orphan*/  CryptMemFree (scalar_t__) ; 
 int /*<<< orphan*/  ERROR_FILE_EXISTS ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  KEY_READ ; 
 int REG_OPENED_EXISTING_KEY ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegCreateKeyExW (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  RegOpenKeyExW (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (void const*) ; 
 int /*<<< orphan*/  lstrcmpiW (void const*,int /*<<< orphan*/ ) ; 
 int lstrlenW (void const*) ; 
 int /*<<< orphan*/  rootW ; 
 int /*<<< orphan*/  wsprintfW (scalar_t__,char const*,void const*,void const*) ; 

__attribute__((used)) static WINECRYPT_CERTSTORE *CRYPT_SysRegOpenStoreW(HCRYPTPROV hCryptProv,
 DWORD dwFlags, const void *pvPara)
{
    static const WCHAR fmt[] = { '%','s','\\','%','s',0 };
    LPCWSTR storeName = pvPara;
    LPWSTR storePath;
    WINECRYPT_CERTSTORE *store = NULL;
    HKEY root;
    LPCWSTR base;

    TRACE("(%ld, %08x, %s)\n", hCryptProv, dwFlags,
     debugstr_w(pvPara));

    if (!pvPara)
    {
        SetLastError(E_INVALIDARG);
        return NULL;
    }

    switch (dwFlags & CERT_SYSTEM_STORE_LOCATION_MASK)
    {
    case CERT_SYSTEM_STORE_LOCAL_MACHINE:
        root = HKEY_LOCAL_MACHINE;
        base = CERT_LOCAL_MACHINE_SYSTEM_STORE_REGPATH;
        /* If the HKLM\Root certs are requested, expressing system certs into the registry */
        if (!lstrcmpiW(storeName, rootW))
            CRYPT_ImportSystemRootCertsToReg();
        break;
    case CERT_SYSTEM_STORE_CURRENT_USER:
        root = HKEY_CURRENT_USER;
        base = CERT_LOCAL_MACHINE_SYSTEM_STORE_REGPATH;
        break;
    case CERT_SYSTEM_STORE_CURRENT_SERVICE:
        /* hklm\Software\Microsoft\Cryptography\Services\servicename\
         * SystemCertificates
         */
        FIXME("CERT_SYSTEM_STORE_CURRENT_SERVICE, %s: stub\n",
         debugstr_w(storeName));
        return NULL;
    case CERT_SYSTEM_STORE_SERVICES:
        /* hklm\Software\Microsoft\Cryptography\Services\servicename\
         * SystemCertificates
         */
        FIXME("CERT_SYSTEM_STORE_SERVICES, %s: stub\n",
         debugstr_w(storeName));
        return NULL;
    case CERT_SYSTEM_STORE_USERS:
        /* hku\user sid\Software\Microsoft\SystemCertificates */
        FIXME("CERT_SYSTEM_STORE_USERS, %s: stub\n",
         debugstr_w(storeName));
        return NULL;
    case CERT_SYSTEM_STORE_CURRENT_USER_GROUP_POLICY:
        root = HKEY_CURRENT_USER;
        base = CERT_GROUP_POLICY_SYSTEM_STORE_REGPATH;
        break;
    case CERT_SYSTEM_STORE_LOCAL_MACHINE_GROUP_POLICY:
        root = HKEY_LOCAL_MACHINE;
        base = CERT_GROUP_POLICY_SYSTEM_STORE_REGPATH;
        break;
    case CERT_SYSTEM_STORE_LOCAL_MACHINE_ENTERPRISE:
        /* hklm\Software\Microsoft\EnterpriseCertificates */
        FIXME("CERT_SYSTEM_STORE_LOCAL_MACHINE_ENTERPRISE, %s: stub\n",
         debugstr_w(storeName));
        return NULL;
    default:
        SetLastError(E_INVALIDARG);
        return NULL;
    }

    storePath = CryptMemAlloc((lstrlenW(base) + lstrlenW(storeName) + 2) *
     sizeof(WCHAR));
    if (storePath)
    {
        LONG rc;
        HKEY key;
        REGSAM sam = dwFlags & CERT_STORE_READONLY_FLAG ? KEY_READ :
            KEY_ALL_ACCESS;

        wsprintfW(storePath, fmt, base, storeName);
        if (dwFlags & CERT_STORE_OPEN_EXISTING_FLAG)
            rc = RegOpenKeyExW(root, storePath, 0, sam, &key);
        else
        {
            DWORD disp;

            rc = RegCreateKeyExW(root, storePath, 0, NULL, 0, sam, NULL,
                                 &key, &disp);
            if (!rc && dwFlags & CERT_STORE_CREATE_NEW_FLAG &&
                disp == REG_OPENED_EXISTING_KEY)
            {
                RegCloseKey(key);
                rc = ERROR_FILE_EXISTS;
            }
        }
        if (!rc)
        {
            store = CRYPT_RegOpenStore(hCryptProv, dwFlags, key);
            RegCloseKey(key);
        }
        else
            SetLastError(rc);
        CryptMemFree(storePath);
    }
    return store;
}