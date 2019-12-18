#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_8__ {int /*<<< orphan*/  strings_stream; int /*<<< orphan*/  pStorage; int /*<<< orphan*/  pITStorage; int /*<<< orphan*/  szFile; int /*<<< orphan*/  codePage; } ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ CHMInfo ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_ITStorage ; 
 int /*<<< orphan*/  CP_ACP ; 
 TYPE_1__* CloseCHM (TYPE_1__*) ; 
 int /*<<< orphan*/  CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IITStorage ; 
 int /*<<< orphan*/  IITStorage_StgOpenStorage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStorage_OpenStream (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReadChmSystem (TYPE_1__*) ; 
 int STGM_READ ; 
 int STGM_SHARE_DENY_WRITE ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 TYPE_1__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  heap_free (TYPE_1__*) ; 
 int /*<<< orphan*/  strdupW (int /*<<< orphan*/ ) ; 

CHMInfo *OpenCHM(LPCWSTR szFile)
{
    HRESULT hres;
    CHMInfo *ret;

    static const WCHAR wszSTRINGS[] = {'#','S','T','R','I','N','G','S',0};

    if (!(ret = heap_alloc_zero(sizeof(CHMInfo))))
        return NULL;
    ret->codePage = CP_ACP;

    if (!(ret->szFile = strdupW(szFile))) {
        heap_free(ret);
        return NULL;
    }

    hres = CoCreateInstance(&CLSID_ITStorage, NULL, CLSCTX_INPROC_SERVER,
            &IID_IITStorage, (void **) &ret->pITStorage) ;
    if(FAILED(hres)) {
        WARN("Could not create ITStorage: %08x\n", hres);
        return CloseCHM(ret);
    }

    hres = IITStorage_StgOpenStorage(ret->pITStorage, szFile, NULL,
            STGM_READ | STGM_SHARE_DENY_WRITE, NULL, 0, &ret->pStorage);
    if(FAILED(hres)) {
        WARN("Could not open storage: %08x\n", hres);
        return CloseCHM(ret);
    }
    hres = IStorage_OpenStream(ret->pStorage, wszSTRINGS, NULL, STGM_READ, 0,
            &ret->strings_stream);
    if(FAILED(hres)) {
        WARN("Could not open #STRINGS stream: %08x\n", hres);
        /* It's not critical, so we pass */
    }

    if(!ReadChmSystem(ret)) {
        WARN("Could not read #SYSTEM\n");
        return CloseCHM(ret);
    }

    return ret;
}