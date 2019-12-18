#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int WORD ;
typedef  int WCHAR ;
struct TYPE_9__ {int /*<<< orphan*/  nGroups; int /*<<< orphan*/  groups; } ;
struct TYPE_8__ {int /*<<< orphan*/  startGlyphID; int /*<<< orphan*/  startCharCode; } ;
struct TYPE_7__ {scalar_t__ CMAP_format12_Table; } ;
typedef  TYPE_1__ ScriptCache ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int DWORD ;
typedef  TYPE_2__ CMAP_SegmentedCoverage_group ;
typedef  TYPE_3__ CMAP_SegmentedCoverage ;

/* Variables and functions */
 int GET_BE_DWORD (int /*<<< orphan*/ ) ; 
 int GGI_MARK_NONEXISTING_GLYPHS ; 
 int GetGlyphIndicesW (int /*<<< orphan*/ ,int*,int,int*,int) ; 
 TYPE_2__* bsearch (int*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compare_group ; 
 scalar_t__ load_CMAP_format12_table (int /*<<< orphan*/ ,TYPE_1__*) ; 

DWORD OpenType_CMAP_GetGlyphIndex(HDC hdc, ScriptCache *psc, DWORD utf32c, WORD *glyph_index, DWORD flags)
{
    /* BMP: use gdi32 for ease */
    if (utf32c < 0x10000)
    {
        WCHAR ch = utf32c;
        return GetGlyphIndicesW(hdc, &ch, 1, glyph_index, flags);
    }

    if (!psc->CMAP_format12_Table)
        psc->CMAP_format12_Table = load_CMAP_format12_table(hdc, psc);

    if (flags & GGI_MARK_NONEXISTING_GLYPHS)
        *glyph_index = 0xffffu;
    else
        *glyph_index = 0u;

    if (psc->CMAP_format12_Table)
    {
        CMAP_SegmentedCoverage *format = NULL;
        CMAP_SegmentedCoverage_group *group = NULL;

        format = (CMAP_SegmentedCoverage *)psc->CMAP_format12_Table;

        group = bsearch(&utf32c, format->groups, GET_BE_DWORD(format->nGroups),
                        sizeof(CMAP_SegmentedCoverage_group), compare_group);

        if (group)
        {
            DWORD offset = utf32c - GET_BE_DWORD(group->startCharCode);
            *glyph_index = GET_BE_DWORD(group->startGlyphID) + offset;
            return 0;
        }
    }
    return 0;
}