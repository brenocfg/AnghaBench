#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_8__ {int fClusterStart; int fZeroWidth; int /*<<< orphan*/  uJustification; scalar_t__ fDiacritic; } ;
struct TYPE_10__ {TYPE_2__ sva; } ;
struct TYPE_7__ {scalar_t__ const wgDefault; } ;
struct TYPE_9__ {TYPE_1__ sfp; } ;
typedef  TYPE_3__ ScriptCache ;
typedef  TYPE_4__ SCRIPT_GLYPHPROP ;
typedef  int /*<<< orphan*/  SCRIPT_CHARPROP ;
typedef  int /*<<< orphan*/  SCRIPT_ANALYSIS ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  SCRIPT_JUSTIFY_BLANK ; 

__attribute__((used)) static void ShapeCharGlyphProp_Control( HDC hdc, ScriptCache *psc, SCRIPT_ANALYSIS *psa, const WCHAR* pwcChars, const INT cChars, const WORD* pwGlyphs, const INT cGlyphs, WORD *pwLogClust, SCRIPT_CHARPROP *pCharProp, SCRIPT_GLYPHPROP *pGlyphProp )
{
    int i;
    for (i = 0; i < cGlyphs; i++)
    {
        pGlyphProp[i].sva.fClusterStart = 1;
        pGlyphProp[i].sva.fDiacritic = 0;
        pGlyphProp[i].sva.uJustification = SCRIPT_JUSTIFY_BLANK;

        if (pwGlyphs[i] == psc->sfp.wgDefault)
            pGlyphProp[i].sva.fZeroWidth = 0;
        else
            pGlyphProp[i].sva.fZeroWidth = 1;
    }
}