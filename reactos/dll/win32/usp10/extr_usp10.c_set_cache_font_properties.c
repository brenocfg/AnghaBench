#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int WORD ;
typedef  int WCHAR ;
struct TYPE_6__ {int cBytes; int wgBlank; int wgInvalid; int wgKashida; scalar_t__ iKashidaWidth; scalar_t__ wgDefault; } ;
struct TYPE_5__ {int tmBreakChar; scalar_t__ tmDefaultChar; } ;
struct TYPE_7__ {TYPE_2__ sfp; TYPE_1__ tm; int /*<<< orphan*/  sfnt; } ;
typedef  TYPE_3__ ScriptCache ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GDI_ERROR ; 
 int /*<<< orphan*/  GGI_MARK_NONEXISTING_GLYPHS ; 
 scalar_t__ GetGlyphIndicesW (int /*<<< orphan*/  const,int const*,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static inline BOOL set_cache_font_properties(const HDC hdc, ScriptCache *sc)
{
    sc->sfp.cBytes = sizeof(sc->sfp);

    if (!sc->sfnt)
    {
        sc->sfp.wgBlank = sc->tm.tmBreakChar;
        sc->sfp.wgDefault = sc->tm.tmDefaultChar;
        sc->sfp.wgInvalid = sc->sfp.wgBlank;
        sc->sfp.wgKashida = 0xFFFF;
        sc->sfp.iKashidaWidth = 0;
    }
    else
    {
        static const WCHAR chars[4] = {0x0020, 0x200B, 0xF71B, 0x0640};
        /* U+0020: numeric space
           U+200B: zero width space
           U+F71B: unknown char found by black box testing
           U+0640: kashida */
        WORD gi[4];

        if (GetGlyphIndicesW(hdc, chars, 4, gi, GGI_MARK_NONEXISTING_GLYPHS) != GDI_ERROR)
        {
            if(gi[0] != 0xFFFF) /* 0xFFFF: index of default non exist char */
                sc->sfp.wgBlank = gi[0];
            else
                sc->sfp.wgBlank = 0;

            sc->sfp.wgDefault = 0;

            if (gi[2] != 0xFFFF)
                sc->sfp.wgInvalid = gi[2];
            else if (gi[1] != 0xFFFF)
                sc->sfp.wgInvalid = gi[1];
            else if (gi[0] != 0xFFFF)
                sc->sfp.wgInvalid = gi[0];
            else
                sc->sfp.wgInvalid = 0;

            sc->sfp.wgKashida = gi[3];

            sc->sfp.iKashidaWidth = 0; /* TODO */
        }
        else
            return FALSE;
    }
    return TRUE;
}