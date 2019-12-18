#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int dwStoreProvFlags; int /*<<< orphan*/ * provControl; int /*<<< orphan*/ * provDeleteCtl; int /*<<< orphan*/ * provWriteCtl; int /*<<< orphan*/ * provDeleteCrl; int /*<<< orphan*/ * provWriteCrl; int /*<<< orphan*/ * provDeleteCert; int /*<<< orphan*/ * provWriteCert; int /*<<< orphan*/ * provCloseStore; int /*<<< orphan*/  hStoreProv; int /*<<< orphan*/ * memStore; int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ WINE_PROVIDERSTORE ;
typedef  int /*<<< orphan*/  WINECRYPT_CERTSTORE ;
struct TYPE_6__ {int dwStoreProvFlags; size_t cStoreProvFunc; int /*<<< orphan*/ ** rgpvStoreProvFunc; int /*<<< orphan*/  hStoreProv; } ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_2__ CERT_STORE_PROV_INFO ;

/* Variables and functions */
 size_t CERT_STORE_PROV_CLOSE_FUNC ; 
 size_t CERT_STORE_PROV_CONTROL_FUNC ; 
 size_t CERT_STORE_PROV_DELETE_CERT_FUNC ; 
 size_t CERT_STORE_PROV_DELETE_CRL_FUNC ; 
 size_t CERT_STORE_PROV_DELETE_CTL_FUNC ; 
 int CERT_STORE_PROV_EXTERNAL_FLAG ; 
 size_t CERT_STORE_PROV_WRITE_CERT_FUNC ; 
 size_t CERT_STORE_PROV_WRITE_CRL_FUNC ; 
 size_t CERT_STORE_PROV_WRITE_CTL_FUNC ; 
 int /*<<< orphan*/  CRYPT_InitStore (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CertCloseStore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* CryptMemAlloc (int) ; 
 int /*<<< orphan*/  ProvStoreVtbl ; 
 int /*<<< orphan*/  StoreTypeProvider ; 

WINECRYPT_CERTSTORE *CRYPT_ProvCreateStore(DWORD dwFlags,
 WINECRYPT_CERTSTORE *memStore, const CERT_STORE_PROV_INFO *pProvInfo)
{
    WINE_PROVIDERSTORE *ret = CryptMemAlloc(sizeof(WINE_PROVIDERSTORE));

    if (ret)
    {
        CRYPT_InitStore(&ret->hdr, dwFlags, StoreTypeProvider, &ProvStoreVtbl);
        ret->dwStoreProvFlags = pProvInfo->dwStoreProvFlags;
        if (ret->dwStoreProvFlags & CERT_STORE_PROV_EXTERNAL_FLAG)
        {
            CertCloseStore(memStore, 0);
            ret->memStore = NULL;
        }
        else
            ret->memStore = memStore;
        ret->hStoreProv = pProvInfo->hStoreProv;
        if (pProvInfo->cStoreProvFunc > CERT_STORE_PROV_CLOSE_FUNC)
            ret->provCloseStore =
             pProvInfo->rgpvStoreProvFunc[CERT_STORE_PROV_CLOSE_FUNC];
        else
            ret->provCloseStore = NULL;
        if (pProvInfo->cStoreProvFunc >
         CERT_STORE_PROV_WRITE_CERT_FUNC)
            ret->provWriteCert = pProvInfo->rgpvStoreProvFunc[
             CERT_STORE_PROV_WRITE_CERT_FUNC];
        else
            ret->provWriteCert = NULL;
        if (pProvInfo->cStoreProvFunc >
         CERT_STORE_PROV_DELETE_CERT_FUNC)
            ret->provDeleteCert = pProvInfo->rgpvStoreProvFunc[
             CERT_STORE_PROV_DELETE_CERT_FUNC];
        else
            ret->provDeleteCert = NULL;
        if (pProvInfo->cStoreProvFunc >
         CERT_STORE_PROV_WRITE_CRL_FUNC)
            ret->provWriteCrl = pProvInfo->rgpvStoreProvFunc[
             CERT_STORE_PROV_WRITE_CRL_FUNC];
        else
            ret->provWriteCrl = NULL;
        if (pProvInfo->cStoreProvFunc >
         CERT_STORE_PROV_DELETE_CRL_FUNC)
            ret->provDeleteCrl = pProvInfo->rgpvStoreProvFunc[
             CERT_STORE_PROV_DELETE_CRL_FUNC];
        else
            ret->provDeleteCrl = NULL;
        if (pProvInfo->cStoreProvFunc >
         CERT_STORE_PROV_WRITE_CTL_FUNC)
            ret->provWriteCtl = pProvInfo->rgpvStoreProvFunc[
             CERT_STORE_PROV_WRITE_CTL_FUNC];
        else
            ret->provWriteCtl = NULL;
        if (pProvInfo->cStoreProvFunc >
         CERT_STORE_PROV_DELETE_CTL_FUNC)
            ret->provDeleteCtl = pProvInfo->rgpvStoreProvFunc[
             CERT_STORE_PROV_DELETE_CTL_FUNC];
        else
            ret->provDeleteCtl = NULL;
        if (pProvInfo->cStoreProvFunc >
         CERT_STORE_PROV_CONTROL_FUNC)
            ret->provControl = pProvInfo->rgpvStoreProvFunc[
             CERT_STORE_PROV_CONTROL_FUNC];
        else
            ret->provControl = NULL;
    }
    return (WINECRYPT_CERTSTORE*)ret;
}