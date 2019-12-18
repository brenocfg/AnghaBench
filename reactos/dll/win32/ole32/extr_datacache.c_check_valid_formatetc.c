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
struct TYPE_3__ {scalar_t__ dwAspect; scalar_t__ cfFormat; scalar_t__ tymed; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ FORMATETC ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_S_FORMATETC_NOTSUPPORTED ; 
 scalar_t__ CF_BITMAP ; 
 scalar_t__ CF_DIB ; 
 scalar_t__ CF_ENHMETAFILE ; 
 scalar_t__ CF_METAFILEPICT ; 
 scalar_t__ DVASPECT_ICON ; 
 int /*<<< orphan*/  DV_E_FORMATETC ; 
 int /*<<< orphan*/  DV_E_TYMED ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ TYMED_ENHMF ; 
 scalar_t__ TYMED_GDI ; 
 scalar_t__ TYMED_HGLOBAL ; 
 scalar_t__ TYMED_MFPICT ; 
 int /*<<< orphan*/  WARN (char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static HRESULT check_valid_formatetc( const FORMATETC *fmt )
{
    /* DVASPECT_ICON must be CF_METAFILEPICT */
    if (fmt->dwAspect == DVASPECT_ICON && fmt->cfFormat != CF_METAFILEPICT)
        return DV_E_FORMATETC;

    if (!fmt->cfFormat ||
        (fmt->cfFormat == CF_METAFILEPICT && fmt->tymed == TYMED_MFPICT) ||
        (fmt->cfFormat == CF_BITMAP && fmt->tymed == TYMED_GDI) ||
        (fmt->cfFormat == CF_DIB && fmt->tymed == TYMED_HGLOBAL) ||
        (fmt->cfFormat == CF_ENHMETAFILE && fmt->tymed == TYMED_ENHMF))
        return S_OK;
    else if (fmt->tymed == TYMED_HGLOBAL)
        return CACHE_S_FORMATETC_NOTSUPPORTED;
    else
    {
        WARN("invalid clipformat/tymed combination: %d/%d\n", fmt->cfFormat, fmt->tymed);
        return DV_E_TYMED;
    }
}