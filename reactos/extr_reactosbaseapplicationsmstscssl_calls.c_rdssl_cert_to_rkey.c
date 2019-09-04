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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_5__ {TYPE_1__* pCertInfo; } ;
struct TYPE_4__ {int /*<<< orphan*/  SubjectPublicKeyInfo; } ;
typedef  TYPE_2__* PCCERT_CONTEXT ;
typedef  int /*<<< orphan*/  HCRYPTPROV ;
typedef  int /*<<< orphan*/  HCRYPTKEY ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPT_NEWKEYSET ; 
 scalar_t__ CryptAcquireContext (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CryptDestroyKey (int /*<<< orphan*/ ) ; 
 scalar_t__ CryptExportKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ CryptImportPublicKeyInfoEx (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CryptReleaseContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  MS_ENHANCED_PROV ; 
 scalar_t__ NTE_BAD_KEYSET ; 
 int PKCS_7_ASN_ENCODING ; 
 int /*<<< orphan*/  PROV_RSA_FULL ; 
 int /*<<< orphan*/  PUBLICKEYBLOB ; 
 int X509_ASN_ENCODING ; 
 int /*<<< orphan*/  error (char*,scalar_t__) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_malloc (scalar_t__,int /*<<< orphan*/ ) ; 

uint8 *rdssl_cert_to_rkey(PCCERT_CONTEXT cert, uint32 * key_len)
{
    HCRYPTPROV hCryptProv;
    HCRYPTKEY hKey;
    BOOL ret;
    BYTE * rkey;
    DWORD dwSize, dwErr;
    ret = CryptAcquireContext(&hCryptProv,
                              NULL,
                              MS_ENHANCED_PROV,
                              PROV_RSA_FULL,
                              0);
    if (!ret)
    {
        dwErr = GetLastError();
        if (dwErr == NTE_BAD_KEYSET)
        {
            ret = CryptAcquireContext(&hCryptProv,
                                      L"MSTSC",
                                      MS_ENHANCED_PROV,
                                      PROV_RSA_FULL,
                                      CRYPT_NEWKEYSET);
        }
    }
    if (!ret)
    {
        dwErr = GetLastError();
        error("CryptAcquireContext call failed with %lx\n", dwErr);
        return NULL;
    }
    ret = CryptImportPublicKeyInfoEx(hCryptProv,
                                     X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
                                     &(cert->pCertInfo->SubjectPublicKeyInfo),
                                     0,
                                     0,
                                     NULL,
                                     &hKey);
    if (!ret)
    {
        dwErr = GetLastError();
        CryptReleaseContext(hCryptProv, 0);
        error("CryptImportPublicKeyInfoEx call failed with %lx\n", dwErr);
        return NULL;
    }
    ret = CryptExportKey(hKey,
                         0,
                         PUBLICKEYBLOB,
                         0,
                         NULL,
                         &dwSize);
    if (!ret)
    {
        dwErr = GetLastError();
        CryptDestroyKey(hKey);
        CryptReleaseContext(hCryptProv, 0);
        error("CryptExportKey call failed with %lx\n", dwErr);
        return NULL;
    }
    rkey = g_malloc(dwSize, 0);
    ret = CryptExportKey(hKey,
                         0,
                         PUBLICKEYBLOB,
                         0,
                         rkey,
                         &dwSize);
    if (!ret)
    {
        dwErr = GetLastError();
        g_free(rkey);
        CryptDestroyKey(hKey);
        CryptReleaseContext(hCryptProv, 0);
        error("CryptExportKey call failed with %lx\n", dwErr);
        return NULL;
    }
    CryptDestroyKey(hKey);
    CryptReleaseContext(hCryptProv, 0);
    return rkey;
}