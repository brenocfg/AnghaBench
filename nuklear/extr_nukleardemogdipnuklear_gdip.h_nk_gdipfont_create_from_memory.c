#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t curFontCollection; int /*<<< orphan*/ * fontCollection; } ;
typedef  int /*<<< orphan*/  GdipFont ;

/* Variables and functions */
 scalar_t__ GdipNewPrivateFontCollection (int /*<<< orphan*/ *) ; 
 scalar_t__ GdipPrivateAddMemoryFont (int /*<<< orphan*/ ,void const*,int) ; 
 TYPE_1__ gdip ; 
 int /*<<< orphan*/  nk_gdip_getCurFontCollection () ; 
 int /*<<< orphan*/ * nk_gdipfont_create_from_collection (int) ; 

GdipFont*
nk_gdipfont_create_from_memory(const void* membuf, int membufSize, int size)
{
    if( !nk_gdip_getCurFontCollection() )
        if( GdipNewPrivateFontCollection(&gdip.fontCollection[gdip.curFontCollection]) ) return NULL;
    if( GdipPrivateAddMemoryFont(nk_gdip_getCurFontCollection(), membuf, membufSize) ) return NULL;
    return nk_gdipfont_create_from_collection(size);
}