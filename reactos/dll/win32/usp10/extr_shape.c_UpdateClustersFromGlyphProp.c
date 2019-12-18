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
typedef  int WORD ;
struct TYPE_4__ {scalar_t__ fClusterStart; } ;
struct TYPE_5__ {TYPE_1__ sva; } ;
typedef  TYPE_2__ SCRIPT_GLYPHPROP ;

/* Variables and functions */

__attribute__((used)) static void UpdateClustersFromGlyphProp(const int cGlyphs, const int cChars, WORD* pwLogClust, SCRIPT_GLYPHPROP *pGlyphProp)
{
    int i;

    for (i = 0; i < cGlyphs; i++)
    {
        if (!pGlyphProp[i].sva.fClusterStart)
        {
            int j;
            for (j = 0; j < cChars; j++)
            {
                if (pwLogClust[j] == i)
                {
                    int k = j;
                    while (k >= 0 && k <cChars && !pGlyphProp[pwLogClust[k]].sva.fClusterStart)
                        k-=1;
                    if (k >= 0 && k <cChars && pGlyphProp[pwLogClust[k]].sva.fClusterStart)
                        pwLogClust[j] = pwLogClust[k];
                }
            }
        }
    }
}