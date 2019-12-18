#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  med ;
struct TYPE_11__ {int /*<<< orphan*/  tymed; } ;
struct TYPE_9__ {int /*<<< orphan*/  hBitmap; } ;
struct TYPE_10__ {TYPE_1__ u; } ;
typedef  TYPE_2__ STGMEDIUM ;
typedef  int /*<<< orphan*/  IDataObject ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/ * HBITMAP ;
typedef  TYPE_3__ FORMATETC ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDataObject_GetData (int /*<<< orphan*/ *,TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ReleaseStgMedium (TYPE_2__*) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYMED_GDI ; 
 int /*<<< orphan*/  dup_bitmap (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static HRESULT get_data_from_bitmap(IDataObject *data, FORMATETC *fmt, HBITMAP *hbm)
{
    HBITMAP copy;
    HRESULT hr;
    FORMATETC mem_fmt;
    STGMEDIUM med;

    *hbm = NULL;

    mem_fmt = *fmt;
    mem_fmt.tymed = TYMED_GDI;
    memset(&med, 0, sizeof(med));

    hr = IDataObject_GetData(data, &mem_fmt, &med);
    if(FAILED(hr)) return hr;

    hr = dup_bitmap(med.u.hBitmap, &copy);

    if(SUCCEEDED(hr)) *hbm = copy;

    ReleaseStgMedium(&med);

    return hr;
}