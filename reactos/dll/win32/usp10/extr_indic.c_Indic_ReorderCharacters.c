#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  (* reorder_function ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  lexical_function ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  ScriptCache ;
typedef  int /*<<< orphan*/  SCRIPT_ANALYSIS ;
typedef  int /*<<< orphan*/  IndicSyllable ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  Indic_ParseSyllables (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void Indic_ReorderCharacters(HDC hdc, SCRIPT_ANALYSIS *psa, ScriptCache *psc, WCHAR *input, unsigned int cChar,
        IndicSyllable **syllables, int *syllable_count, lexical_function lex, reorder_function reorder_f, BOOL modern)
{
    int i;

    if (!reorder_f)
    {
        ERR("Failure to have required functions\n");
        return;
    }

    Indic_ParseSyllables(hdc, psa, psc, input, cChar, syllables, syllable_count, lex, modern);
    for (i = 0; i < *syllable_count; i++)
        reorder_f(input, &(*syllables)[i], lex);
}