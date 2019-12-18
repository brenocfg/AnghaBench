#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lexical_function ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {scalar_t__ pref; int base; } ;
typedef  TYPE_1__ IndicSyllable ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,size_t,int) ; 

__attribute__((used)) static void SecondReorder_Pref_precede_base(const IndicSyllable *s,
        WORD *glyphs, const IndicSyllable *g, lexical_function lexical)
{
    if (s->pref >= 0 && g->pref > g->base)
    {
        int j;
        WCHAR og = glyphs[g->pref];
        TRACE("Doing reorder of pref from %i to %i\n",g->pref,g->base);
        for (j = g->pref; j > g->base; j--)
            glyphs[j] = glyphs[j-1];
        glyphs[g->base] = og;
    }
}