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
typedef  int /*<<< orphan*/  provInfo ;
struct TYPE_5__ {int /*<<< orphan*/  dirty; void* type; int /*<<< orphan*/  file; int /*<<< orphan*/  memStore; void* dwOpenFlags; } ;
typedef  TYPE_1__ WINE_FILESTOREINFO ;
typedef  int /*<<< orphan*/  WINECRYPT_CERTSTORE ;
struct TYPE_6__ {int cbSize; TYPE_1__* hStoreProv; int /*<<< orphan*/  rgpvStoreProvFunc; int /*<<< orphan*/  cStoreProvFunc; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  HCERTSTORE ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  void* DWORD ;
typedef  TYPE_2__ CERT_STORE_PROV_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CRYPT_ProvCreateStore (void*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_1__* CryptMemAlloc (int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  fileProvFuncs ; 

__attribute__((used)) static WINECRYPT_CERTSTORE *CRYPT_CreateFileStore(DWORD dwFlags,
 HCERTSTORE memStore, HANDLE file, DWORD type)
{
    WINECRYPT_CERTSTORE *store = NULL;
    WINE_FILESTOREINFO *info = CryptMemAlloc(sizeof(WINE_FILESTOREINFO));

    if (info)
    {
        CERT_STORE_PROV_INFO provInfo = { 0 };

        info->dwOpenFlags = dwFlags;
        info->memStore = memStore;
        info->file = file;
        info->type = type;
        info->dirty = FALSE;
        provInfo.cbSize = sizeof(provInfo);
        provInfo.cStoreProvFunc = ARRAY_SIZE(fileProvFuncs);
        provInfo.rgpvStoreProvFunc = fileProvFuncs;
        provInfo.hStoreProv = info;
        store = CRYPT_ProvCreateStore(dwFlags, memStore, &provInfo);
    }
    return store;
}