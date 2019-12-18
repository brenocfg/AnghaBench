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
struct TYPE_3__ {scalar_t__ hMF; } ;
typedef  TYPE_1__ METAFILEPICT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/ * HGLOBAL ;

/* Variables and functions */
 scalar_t__ CopyMetaFileW (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  E_FAIL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int GMEM_DDESHARE ; 
 int GMEM_MOVEABLE ; 
 int /*<<< orphan*/  GlobalFree (int /*<<< orphan*/ *) ; 
 TYPE_1__* GlobalLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  dup_global_mem (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 

__attribute__((used)) static HRESULT dup_metafilepict(HGLOBAL src, HGLOBAL *pdest)
{
    HRESULT hr;
    HGLOBAL dest;
    METAFILEPICT *dest_ptr;

    *pdest = NULL;

    /* Copy the METAFILEPICT structure. */
    hr = dup_global_mem(src, GMEM_DDESHARE|GMEM_MOVEABLE, &dest);
    if (FAILED(hr)) return hr;

    dest_ptr = GlobalLock(dest);
    if (!dest_ptr) return E_FAIL;

    /* Give the new METAFILEPICT a separate HMETAFILE. */
    dest_ptr->hMF = CopyMetaFileW(dest_ptr->hMF, NULL);
    if (dest_ptr->hMF)
    {
       GlobalUnlock(dest);
       *pdest = dest;
       return S_OK;
    }
    else
    {
       GlobalUnlock(dest);
       GlobalFree(dest);
       return E_FAIL;
    }
}