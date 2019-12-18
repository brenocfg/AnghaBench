#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  hMF; } ;
struct TYPE_6__ {int /*<<< orphan*/  hGlobal; int /*<<< orphan*/  hMetaFilePict; } ;
struct TYPE_7__ {scalar_t__ tymed; scalar_t__ pUnkForRelease; TYPE_1__ u; } ;
typedef  TYPE_2__ STGMEDIUM ;
typedef  TYPE_3__ METAFILEPICT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  CLIPFORMAT ;

/* Variables and functions */
 int /*<<< orphan*/  CopyMetaFileW (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DV_E_STGMEDIUM ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GMEM_MOVEABLE ; 
 int /*<<< orphan*/  GlobalAlloc (int /*<<< orphan*/ ,int) ; 
 void* GlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IUnknown_AddRef (scalar_t__) ; 
 int /*<<< orphan*/  OleDuplicateData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ TYMED_MFPICT ; 
 scalar_t__ TYMED_NULL ; 

__attribute__((used)) static HRESULT copy_stg_medium(CLIPFORMAT cf, STGMEDIUM *dest_stgm,
                               const STGMEDIUM *src_stgm)
{
    if (src_stgm->tymed == TYMED_MFPICT)
    {
        const METAFILEPICT *src_mfpict = GlobalLock(src_stgm->u.hMetaFilePict);
        METAFILEPICT *dest_mfpict;

        if (!src_mfpict)
            return DV_E_STGMEDIUM;
        dest_stgm->u.hMetaFilePict = GlobalAlloc(GMEM_MOVEABLE, sizeof(METAFILEPICT));
        dest_mfpict = GlobalLock(dest_stgm->u.hMetaFilePict);
        if (!dest_mfpict)
        {
            GlobalUnlock(src_stgm->u.hMetaFilePict);
            return E_OUTOFMEMORY;
        }
        *dest_mfpict = *src_mfpict;
        dest_mfpict->hMF = CopyMetaFileW(src_mfpict->hMF, NULL);
        GlobalUnlock(src_stgm->u.hMetaFilePict);
        GlobalUnlock(dest_stgm->u.hMetaFilePict);
    }
    else if (src_stgm->tymed != TYMED_NULL)
    {
        dest_stgm->u.hGlobal = OleDuplicateData(src_stgm->u.hGlobal, cf,
                                                GMEM_MOVEABLE);
        if (!dest_stgm->u.hGlobal)
            return E_OUTOFMEMORY;
    }
    dest_stgm->tymed = src_stgm->tymed;
    dest_stgm->pUnkForRelease = src_stgm->pUnkForRelease;
    if (dest_stgm->pUnkForRelease)
        IUnknown_AddRef(dest_stgm->pUnkForRelease);
    return S_OK;
}