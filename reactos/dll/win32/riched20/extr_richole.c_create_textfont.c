#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ str; } ;
struct TYPE_10__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_9__ {int ref; TYPE_2__ ITextFont_iface; void* set_cache_enabled; void* get_cache_enabled; int /*<<< orphan*/ * range; TYPE_4__* props; } ;
typedef  int /*<<< orphan*/  ITextRange ;
typedef  TYPE_1__ ITextFontImpl ;
typedef  TYPE_2__ ITextFont ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 void* FALSE ; 
 size_t FONT_NAME ; 
 int /*<<< orphan*/  ITextRange_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ SysAllocString (scalar_t__) ; 
 void* TRUE ; 
 TYPE_1__* heap_alloc (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_4__**,TYPE_4__**,int) ; 
 int /*<<< orphan*/  textfont_cache_range_props (TYPE_1__*) ; 
 int /*<<< orphan*/  textfontvtbl ; 

__attribute__((used)) static HRESULT create_textfont(ITextRange *range, const ITextFontImpl *src, ITextFont **ret)
{
    ITextFontImpl *font;

    *ret = NULL;
    font = heap_alloc(sizeof(*font));
    if (!font)
        return E_OUTOFMEMORY;

    font->ITextFont_iface.lpVtbl = &textfontvtbl;
    font->ref = 1;

    if (src) {
        font->range = NULL;
        font->get_cache_enabled = TRUE;
        font->set_cache_enabled = TRUE;
        memcpy(&font->props, &src->props, sizeof(font->props));
        if (font->props[FONT_NAME].str)
            font->props[FONT_NAME].str = SysAllocString(font->props[FONT_NAME].str);
    }
    else {
        font->range = range;
        ITextRange_AddRef(range);

        /* cache current properties */
        font->get_cache_enabled = FALSE;
        font->set_cache_enabled = FALSE;
        textfont_cache_range_props(font);
    }

    *ret = &font->ITextFont_iface;
    return S_OK;
}