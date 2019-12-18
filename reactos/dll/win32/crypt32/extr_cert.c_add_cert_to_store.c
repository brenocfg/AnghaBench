#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hashToAdd ;
typedef  int /*<<< orphan*/  context_t ;
struct TYPE_25__ {TYPE_3__* vtbl; } ;
typedef  TYPE_4__ WINECRYPT_CERTSTORE ;
struct TYPE_27__ {int member_0; int /*<<< orphan*/ * member_1; } ;
struct TYPE_26__ {TYPE_1__* pCertInfo; int /*<<< orphan*/  dwCertEncodingType; } ;
struct TYPE_23__ {scalar_t__ (* addContext ) (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,scalar_t__) ;} ;
struct TYPE_24__ {TYPE_2__ certs; } ;
struct TYPE_22__ {int /*<<< orphan*/  NotBefore; } ;
typedef  TYPE_5__ const* PCCERT_CONTEXT ;
typedef  int DWORD ;
typedef  TYPE_6__ CRYPT_HASH_BLOB ;
typedef  TYPE_5__ CERT_CONTEXT ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CERT_FIND_SHA1_HASH ; 
 int /*<<< orphan*/  CERT_HASH_PROP_ID ; 
#define  CERT_STORE_ADD_ALWAYS 134 
#define  CERT_STORE_ADD_NEW 133 
#define  CERT_STORE_ADD_NEWER 132 
#define  CERT_STORE_ADD_NEWER_INHERIT_PROPERTIES 131 
#define  CERT_STORE_ADD_REPLACE_EXISTING 130 
#define  CERT_STORE_ADD_REPLACE_EXISTING_INHERIT_PROPERTIES 129 
#define  CERT_STORE_ADD_USE_EXISTING 128 
 int /*<<< orphan*/  CRYPT_E_EXISTS ; 
 TYPE_5__* CertDuplicateCertificateContext (TYPE_5__ const*) ; 
 TYPE_5__* CertFindCertificateInStore (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ *) ; 
 scalar_t__ CertGetCertificateContextProperty (TYPE_5__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  CompareFileTime (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Context_CopyProperties (TYPE_5__ const*,TYPE_5__ const*) ; 
 int /*<<< orphan*/  Context_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/ * context_from_ptr (TYPE_5__ const*) ; 
 TYPE_5__ const* context_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,scalar_t__) ; 

__attribute__((used)) static BOOL add_cert_to_store(WINECRYPT_CERTSTORE *store, const CERT_CONTEXT *cert,
 DWORD add_disposition, BOOL use_link, PCCERT_CONTEXT *ret_context)
{
    const CERT_CONTEXT *existing = NULL;
    BOOL ret = TRUE, inherit_props = FALSE;
    context_t *new_context = NULL;

    switch (add_disposition)
    {
    case CERT_STORE_ADD_ALWAYS:
        break;
    case CERT_STORE_ADD_NEW:
    case CERT_STORE_ADD_REPLACE_EXISTING:
    case CERT_STORE_ADD_REPLACE_EXISTING_INHERIT_PROPERTIES:
    case CERT_STORE_ADD_USE_EXISTING:
    case CERT_STORE_ADD_NEWER:
    case CERT_STORE_ADD_NEWER_INHERIT_PROPERTIES:
    {
        BYTE hashToAdd[20];
        DWORD size = sizeof(hashToAdd);

        ret = CertGetCertificateContextProperty(cert, CERT_HASH_PROP_ID,
         hashToAdd, &size);
        if (ret)
        {
            CRYPT_HASH_BLOB blob = { sizeof(hashToAdd), hashToAdd };

            existing = CertFindCertificateInStore(store, cert->dwCertEncodingType, 0,
             CERT_FIND_SHA1_HASH, &blob, NULL);
        }
        break;
    }
    default:
        FIXME("Unimplemented add disposition %d\n", add_disposition);
        SetLastError(E_INVALIDARG);
        return FALSE;
    }

    switch (add_disposition)
    {
    case CERT_STORE_ADD_ALWAYS:
        break;
    case CERT_STORE_ADD_NEW:
        if (existing)
        {
            TRACE("found matching certificate, not adding\n");
            SetLastError(CRYPT_E_EXISTS);
            return FALSE;
        }
        break;
    case CERT_STORE_ADD_REPLACE_EXISTING:
        break;
    case CERT_STORE_ADD_REPLACE_EXISTING_INHERIT_PROPERTIES:
        if (use_link)
            FIXME("CERT_STORE_ADD_REPLACE_EXISTING_INHERIT_PROPERTIES: semi-stub for links\n");
        if (existing)
            inherit_props = TRUE;
        break;
    case CERT_STORE_ADD_USE_EXISTING:
        if(use_link)
            FIXME("CERT_STORE_ADD_USE_EXISTING: semi-stub for links\n");
        if (existing)
        {
            Context_CopyProperties(existing, cert);
            if (ret_context)
                *ret_context = CertDuplicateCertificateContext(existing);
            return TRUE;
        }
        break;
    case CERT_STORE_ADD_NEWER:
        if (existing && CompareFileTime(&existing->pCertInfo->NotBefore, &cert->pCertInfo->NotBefore) >= 0)
        {
            TRACE("existing certificate is newer, not adding\n");
            SetLastError(CRYPT_E_EXISTS);
            return FALSE;
        }
        break;
    case CERT_STORE_ADD_NEWER_INHERIT_PROPERTIES:
        if (existing)
        {
            if (CompareFileTime(&existing->pCertInfo->NotBefore, &cert->pCertInfo->NotBefore) >= 0)
            {
                TRACE("existing certificate is newer, not adding\n");
                SetLastError(CRYPT_E_EXISTS);
                return FALSE;
            }
            inherit_props = TRUE;
        }
        break;
    }

    /* FIXME: We have tests that this works, but what should we really do in this case? */
    if(!store) {
        if(ret_context)
            *ret_context = CertDuplicateCertificateContext(cert);
        return TRUE;
    }

    ret = store->vtbl->certs.addContext(store, context_from_ptr(cert), existing ? context_from_ptr(existing) : NULL,
     (ret_context || inherit_props) ? &new_context : NULL, use_link);
    if(!ret)
        return FALSE;

    if(inherit_props)
        Context_CopyProperties(context_ptr(new_context), existing);

    if(ret_context)
        *ret_context = context_ptr(new_context);
    else if(new_context)
        Context_Release(new_context);

    TRACE("returning %d\n", ret);
    return ret;
}