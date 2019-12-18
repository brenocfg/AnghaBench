#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ (* lexical_function ) (int /*<<< orphan*/  const) ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_8__ {size_t start; size_t base; size_t end; } ;
typedef  TYPE_1__ IndicSyllable ;

/* Variables and functions */
 int /*<<< orphan*/  SecondReorder_Matra_precede_base (int /*<<< orphan*/  const*,TYPE_1__ const*,int /*<<< orphan*/ *,TYPE_1__ const*,scalar_t__ (*) (int /*<<< orphan*/  const)) ; 
 int /*<<< orphan*/  SecondReorder_Pref_precede_base (TYPE_1__ const*,int /*<<< orphan*/ *,TYPE_1__ const*,scalar_t__ (*) (int /*<<< orphan*/  const)) ; 
 int /*<<< orphan*/  TRACE (char*,size_t,size_t,size_t) ; 
 scalar_t__ lex_Vowel ; 

__attribute__((used)) static void SecondReorder_Like_Tamil(const WCHAR *chars, const IndicSyllable *s,
        WORD *glyphs, const IndicSyllable *g, lexical_function lexical)
{
    TRACE("Syllable (%i..%i..%i)\n",s->start,s->base,s->end);
    TRACE("Glyphs (%i..%i..%i)\n",g->start,g->base,g->end);
    if (s->start == s->base && s->base == s->end)  return;
    if (lexical(chars[s->base]) == lex_Vowel) return;

    SecondReorder_Matra_precede_base(chars, s, glyphs, g, lexical);
    SecondReorder_Pref_precede_base(s, glyphs, g, lexical);
}