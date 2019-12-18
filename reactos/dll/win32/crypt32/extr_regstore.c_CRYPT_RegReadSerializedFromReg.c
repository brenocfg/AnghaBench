#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hash ;
struct TYPE_5__ {int /*<<< orphan*/  (* addContextToStore ) (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;scalar_t__ (* getProp ) (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ;} ;
typedef  TYPE_1__ WINE_CONTEXT_INTERFACE ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  HCERTSTORE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BlobW ; 
 int /*<<< orphan*/  CERT_HASH_PROP_ID ; 
 int /*<<< orphan*/  CERT_STORE_ADD_REPLACE_EXISTING ; 
#define  CERT_STORE_CERTIFICATE_CONTEXT 130 
#define  CERT_STORE_CRL_CONTEXT 129 
#define  CERT_STORE_CTL_CONTEXT 128 
 int /*<<< orphan*/  CRYPT_HashToStr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* CRYPT_ReadSerializedElement (int /*<<< orphan*/ *,int,int,int*) ; 
 int /*<<< orphan*/  Context_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CryptMemAlloc (int) ; 
 int /*<<< orphan*/  CryptMemFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  KEY_READ ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegEnumKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegOpenKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegQueryValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  context_from_ptr (void const*) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* pCRLInterface ; 
 TYPE_1__* pCTLInterface ; 
 TYPE_1__* pCertInterface ; 
 scalar_t__ stub1 (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void CRYPT_RegReadSerializedFromReg(HKEY key, DWORD contextType,
 HCERTSTORE store)
{
    LONG rc;
    DWORD index = 0;
    WCHAR subKeyName[MAX_PATH];

    do {
        DWORD size = ARRAY_SIZE(subKeyName);

        rc = RegEnumKeyExW(key, index++, subKeyName, &size, NULL, NULL, NULL,
         NULL);
        if (!rc)
        {
            HKEY subKey;

            rc = RegOpenKeyExW(key, subKeyName, 0, KEY_READ, &subKey);
            if (!rc)
            {
                LPBYTE buf = NULL;

                size = 0;
                rc = RegQueryValueExW(subKey, BlobW, NULL, NULL, NULL, &size);
                if (!rc)
                    buf = CryptMemAlloc(size);
                if (buf)
                {
                    rc = RegQueryValueExW(subKey, BlobW, NULL, NULL, buf,
                     &size);
                    if (!rc)
                    {
                        const void *context;
                        DWORD addedType;

                        TRACE("Adding cert with hash %s\n",
                         debugstr_w(subKeyName));
                        context = CRYPT_ReadSerializedElement(buf, size,
                         contextType, &addedType);
                        if (context)
                        {
                            const WINE_CONTEXT_INTERFACE *contextInterface;
                            BYTE hash[20];

                            switch (addedType)
                            {
                            case CERT_STORE_CERTIFICATE_CONTEXT:
                                contextInterface = pCertInterface;
                                break;
                            case CERT_STORE_CRL_CONTEXT:
                                contextInterface = pCRLInterface;
                                break;
                            case CERT_STORE_CTL_CONTEXT:
                                contextInterface = pCTLInterface;
                                break;
                            default:
                                contextInterface = NULL;
                            }
                            if (contextInterface)
                            {
                                size = sizeof(hash);
                                if (contextInterface->getProp(context,
                                 CERT_HASH_PROP_ID, hash, &size))
                                {
                                    WCHAR asciiHash[20 * 2 + 1];

                                    CRYPT_HashToStr(hash, asciiHash);
                                    TRACE("comparing %s\n",
                                     debugstr_w(asciiHash));
                                    TRACE("with %s\n", debugstr_w(subKeyName));
                                    if (!lstrcmpW(asciiHash, subKeyName))
                                    {
                                        TRACE("hash matches, adding\n");
                                        contextInterface->addContextToStore(
                                         store, context,
                                         CERT_STORE_ADD_REPLACE_EXISTING, NULL);
                                    }
                                    else
                                        TRACE("hash doesn't match, ignoring\n");
                                }
                                Context_Release(context_from_ptr(context));
                            }
                        }
                    }
                    CryptMemFree(buf);
                }
                RegCloseKey(subKey);
            }
            /* Ignore intermediate errors, continue enumerating */
            rc = ERROR_SUCCESS;
        }
    } while (!rc);
}