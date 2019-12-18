#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  provInfo ;
typedef  int /*<<< orphan*/  count ;
typedef  int /*<<< orphan*/  WINECRYPT_CERTSTORE ;
struct TYPE_3__ {int cbSize; int /*<<< orphan*/  hStoreProv; int /*<<< orphan*/  rgpvStoreProvFunc; int /*<<< orphan*/  cStoreProvFunc; int /*<<< orphan*/  member_0; } ;
typedef  scalar_t__* LPBYTE ;
typedef  scalar_t__ HCRYPTPROV ;
typedef  int /*<<< orphan*/  HCRYPTMSG ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_1__ CERT_STORE_PROV_INFO ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CERT_STORE_ADD_ALWAYS ; 
 int /*<<< orphan*/  CERT_STORE_CREATE_NEW_FLAG ; 
 scalar_t__ CERT_STORE_NO_CRYPT_RELEASE_FLAG ; 
 int /*<<< orphan*/  CERT_STORE_PROV_MEMORY ; 
 int /*<<< orphan*/  CMSG_CERT_COUNT_PARAM ; 
 int /*<<< orphan*/  CMSG_CERT_PARAM ; 
 int /*<<< orphan*/  CMSG_CRL_COUNT_PARAM ; 
 int /*<<< orphan*/  CMSG_CRL_PARAM ; 
 int /*<<< orphan*/ * CRYPT_ProvCreateStore (scalar_t__,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ CertAddEncodedCRLToStore (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ CertAddEncodedCertificateToStore (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CertCloseStore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CertOpenStore (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__* CryptMemAlloc (scalar_t__) ; 
 int /*<<< orphan*/  CryptMemFree (scalar_t__*) ; 
 int /*<<< orphan*/  CryptMsgDuplicate (int /*<<< orphan*/ ) ; 
 scalar_t__ CryptMsgGetParam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  CryptReleaseContext (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  X509_ASN_ENCODING ; 
 int /*<<< orphan*/  msgProvFuncs ; 

__attribute__((used)) static WINECRYPT_CERTSTORE *CRYPT_MsgOpenStore(HCRYPTPROV hCryptProv,
 DWORD dwFlags, const void *pvPara)
{
    WINECRYPT_CERTSTORE *store = NULL;
    HCRYPTMSG msg = (HCRYPTMSG)pvPara;
    WINECRYPT_CERTSTORE *memStore;

    TRACE("(%ld, %08x, %p)\n", hCryptProv, dwFlags, pvPara);

    memStore = CertOpenStore(CERT_STORE_PROV_MEMORY, 0, 0,
     CERT_STORE_CREATE_NEW_FLAG, NULL);
    if (memStore)
    {
        BOOL ret;
        DWORD size, count, i;

        size = sizeof(count);
        ret = CryptMsgGetParam(msg, CMSG_CERT_COUNT_PARAM, 0, &count, &size);
        for (i = 0; ret && i < count; i++)
        {
            size = 0;
            ret = CryptMsgGetParam(msg, CMSG_CERT_PARAM, i, NULL, &size);
            if (ret)
            {
                LPBYTE buf = CryptMemAlloc(size);

                if (buf)
                {
                    ret = CryptMsgGetParam(msg, CMSG_CERT_PARAM, i, buf, &size);
                    if (ret)
                        ret = CertAddEncodedCertificateToStore(memStore,
                         X509_ASN_ENCODING, buf, size, CERT_STORE_ADD_ALWAYS,
                         NULL);
                    CryptMemFree(buf);
                }
            }
        }
        size = sizeof(count);
        ret = CryptMsgGetParam(msg, CMSG_CRL_COUNT_PARAM, 0, &count, &size);
        for (i = 0; ret && i < count; i++)
        {
            size = 0;
            ret = CryptMsgGetParam(msg, CMSG_CRL_PARAM, i, NULL, &size);
            if (ret)
            {
                LPBYTE buf = CryptMemAlloc(size);

                if (buf)
                {
                    ret = CryptMsgGetParam(msg, CMSG_CRL_PARAM, i, buf, &size);
                    if (ret)
                        ret = CertAddEncodedCRLToStore(memStore,
                         X509_ASN_ENCODING, buf, size, CERT_STORE_ADD_ALWAYS,
                         NULL);
                    CryptMemFree(buf);
                }
            }
        }
        if (ret)
        {
            CERT_STORE_PROV_INFO provInfo = { 0 };

            provInfo.cbSize = sizeof(provInfo);
            provInfo.cStoreProvFunc = ARRAY_SIZE(msgProvFuncs);
            provInfo.rgpvStoreProvFunc = msgProvFuncs;
            provInfo.hStoreProv = CryptMsgDuplicate(msg);
            store = CRYPT_ProvCreateStore(dwFlags, memStore, &provInfo);
            /* Msg store doesn't need crypto provider, so close it */
            if (hCryptProv && !(dwFlags & CERT_STORE_NO_CRYPT_RELEASE_FLAG))
                CryptReleaseContext(hCryptProv, 0);
        }
        else
            CertCloseStore(memStore, 0);
    }
    TRACE("returning %p\n", store);
    return store;
}