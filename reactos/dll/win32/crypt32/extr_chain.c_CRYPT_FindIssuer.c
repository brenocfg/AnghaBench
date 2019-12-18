#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  dwCertEncodingType; } ;
struct TYPE_12__ {unsigned int cUrl; int /*<<< orphan*/ * rgwszUrl; } ;
struct TYPE_11__ {scalar_t__ hWorld; } ;
typedef  int /*<<< orphan*/ * PCCERT_CONTEXT ;
typedef  scalar_t__ HCERTSTORE ;
typedef  int DWORD ;
typedef  TYPE_1__ CertificateChainEngine ;
typedef  TYPE_2__ CRYPT_URL_ARRAY ;
typedef  TYPE_3__ CERT_CONTEXT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int CERT_CHAIN_CACHE_ONLY_URL_RETRIEVAL ; 
 int /*<<< orphan*/  CERT_STORE_ADD_NEW ; 
 int /*<<< orphan*/  CERT_STORE_CREATE_NEW_FLAG ; 
 int /*<<< orphan*/  CERT_STORE_PROV_MEMORY ; 
 int /*<<< orphan*/  CONTEXT_OID_CERTIFICATE ; 
 int /*<<< orphan*/  CRYPT_AIA_RETRIEVAL ; 
 int /*<<< orphan*/  CRYPT_CACHE_ONLY_RETRIEVAL ; 
 int /*<<< orphan*/  CertAddCertificateContextToStore (scalar_t__,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CertCloseStore (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CertFindCertificateInStore (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CertFreeCertificateContext (TYPE_3__*) ; 
 scalar_t__ CertOpenStore (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ CryptGetObjectUrl (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,TYPE_2__*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ CryptRetrieveObjectByUrlW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  URL_OID_CERTIFICATE_ISSUER ; 
 int /*<<< orphan*/ * debugstr_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static PCCERT_CONTEXT CRYPT_FindIssuer(const CertificateChainEngine *engine, const CERT_CONTEXT *cert,
        HCERTSTORE store, DWORD type, void *para, DWORD flags, PCCERT_CONTEXT prev_issuer)
{
    CRYPT_URL_ARRAY *urls;
    PCCERT_CONTEXT issuer;
    DWORD size;
    BOOL res;

    issuer = CertFindCertificateInStore(store, cert->dwCertEncodingType, 0, type, para, prev_issuer);
    if(issuer) {
        TRACE("Found in store %p\n", issuer);
        return issuer;
    }

    /* FIXME: For alternate issuers, we don't search world store nor try to retrieve issuer from URL.
     * This needs more tests.
     */
    if(prev_issuer)
        return NULL;

    if(engine->hWorld) {
        issuer = CertFindCertificateInStore(engine->hWorld, cert->dwCertEncodingType, 0, type, para, NULL);
        if(issuer) {
            TRACE("Found in world %p\n", issuer);
            return issuer;
        }
    }

    res = CryptGetObjectUrl(URL_OID_CERTIFICATE_ISSUER, (void*)cert, 0, NULL, &size, NULL, NULL, NULL);
    if(!res)
        return NULL;

    urls = HeapAlloc(GetProcessHeap(), 0, size);
    if(!urls)
        return NULL;

    res = CryptGetObjectUrl(URL_OID_CERTIFICATE_ISSUER, (void*)cert, 0, urls, &size, NULL, NULL, NULL);
    if(res)
    {
        CERT_CONTEXT *new_cert;
        HCERTSTORE new_store;
        unsigned i;

        for(i=0; i < urls->cUrl; i++)
        {
            TRACE("Trying URL %s\n", debugstr_w(urls->rgwszUrl[i]));

            res = CryptRetrieveObjectByUrlW(urls->rgwszUrl[i], CONTEXT_OID_CERTIFICATE,
             (flags & CERT_CHAIN_CACHE_ONLY_URL_RETRIEVAL) ? CRYPT_CACHE_ONLY_RETRIEVAL : CRYPT_AIA_RETRIEVAL,
             0, (void**)&new_cert, NULL, NULL, NULL, NULL);
            if(!res)
            {
                TRACE("CryptRetrieveObjectByUrlW failed: %u\n", GetLastError());
                continue;
            }

            /* FIXME: Use new_cert->hCertStore once cert ref count bug is fixed. */
            new_store = CertOpenStore(CERT_STORE_PROV_MEMORY, 0, 0, CERT_STORE_CREATE_NEW_FLAG, NULL);
            CertAddCertificateContextToStore(new_store, new_cert, CERT_STORE_ADD_NEW, NULL);
            issuer = CertFindCertificateInStore(new_store, cert->dwCertEncodingType, 0, type, para, NULL);
            CertFreeCertificateContext(new_cert);
            CertCloseStore(new_store, 0);
            if(issuer)
            {
                TRACE("Found downloaded issuer %p\n", issuer);
                break;
            }
        }
    }

    HeapFree(GetProcessHeap(), 0, urls);
    return issuer;
}