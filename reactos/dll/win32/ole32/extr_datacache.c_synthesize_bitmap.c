#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  bmiHeader; } ;
struct TYPE_8__ {int /*<<< orphan*/  hBitmap; } ;
struct TYPE_9__ {int /*<<< orphan*/ * pUnkForRelease; int /*<<< orphan*/  tymed; TYPE_1__ u; } ;
typedef  TYPE_2__ STGMEDIUM ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HGLOBAL ;
typedef  int /*<<< orphan*/  HDC ;
typedef  TYPE_3__ BITMAPINFO ;

/* Variables and functions */
 int /*<<< orphan*/  CBM_INIT ; 
 int /*<<< orphan*/  CreateDIBitmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 TYPE_3__* GlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TYMED_GDI ; 
 int bitmap_info_size (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT synthesize_bitmap( HGLOBAL dib, STGMEDIUM *med )
{
    HRESULT hr = E_FAIL;
    BITMAPINFO *bmi;
    HDC hdc = GetDC( 0 );

    if ((bmi = GlobalLock( dib )))
    {
        /* FIXME: validate data size */
        med->u.hBitmap = CreateDIBitmap( hdc, &bmi->bmiHeader, CBM_INIT,
                                         (char *)bmi + bitmap_info_size( bmi, DIB_RGB_COLORS ),
                                         bmi, DIB_RGB_COLORS );
        GlobalUnlock( dib );
        med->tymed = TYMED_GDI;
        med->pUnkForRelease = NULL;
        hr = S_OK;
    }
    ReleaseDC( 0, hdc );
    return hr;
}