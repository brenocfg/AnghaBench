#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
typedef  int WCHAR ;
struct TYPE_4__ {int /*<<< orphan*/  wgBlank; int /*<<< orphan*/  wgDefault; } ;
struct TYPE_5__ {TYPE_1__ sfp; } ;
typedef  TYPE_2__ ScriptCache ;
typedef  int /*<<< orphan*/  SCRIPT_ANALYSIS ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */

__attribute__((used)) static void ContextualShape_Control(HDC hdc, ScriptCache *psc, SCRIPT_ANALYSIS *psa, WCHAR* pwcChars, INT cChars, WORD* pwOutGlyphs, INT* pcGlyphs, INT cMaxGlyphs, WORD *pwLogClust)
{
    int i;
    for (i=0; i < cChars; i++)
    {
        switch (pwcChars[i])
        {
            case 0x000A:
            case 0x000D:
                pwOutGlyphs[i] = psc->sfp.wgBlank;
                break;
            default:
                if (pwcChars[i] < 0x1C)
                    pwOutGlyphs[i] = psc->sfp.wgDefault;
                else
                    pwOutGlyphs[i] = psc->sfp.wgBlank;
        }
    }
}