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
typedef  scalar_t__ (* lexical_function ) (int /*<<< orphan*/  const) ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {int start; int base; } ;
typedef  TYPE_1__ IndicSyllable ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int,int) ; 
 scalar_t__ lex_Matra_pre ; 

__attribute__((used)) static void SecondReorder_Matra_precede_base(const WCHAR *chars, const IndicSyllable *s,
        WORD *glyphs, const IndicSyllable *g, lexical_function lexical)
{
    int i;

    /* reorder previously moved Matras to correct position*/
    for (i = s->start; i < s->base; i++)
    {
        if (lexical(chars[i]) == lex_Matra_pre)
        {
            int j;
            int g_start = g->start + i - s->start;
            if (g_start < g->base -1 )
            {
                WCHAR og = glyphs[g_start];
                TRACE("Doing reorder of matra from %i to %i\n",g_start,g->base);
                for (j = g_start; j < g->base-1; j++)
                    glyphs[j] = glyphs[j+1];
                glyphs[g->base-1] = og;
            }
        }
    }
}