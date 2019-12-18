#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ (* lexical_function ) (int /*<<< orphan*/  const) ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_7__ {int start; unsigned int base; int ralf; int blwf; int pref; int end; } ;
typedef  int /*<<< orphan*/  ScriptCache ;
typedef  int /*<<< orphan*/  SCRIPT_ANALYSIS ;
typedef  TYPE_1__ IndicSyllable ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  FindBaseConsonant (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_1__*,scalar_t__ (*) (int /*<<< orphan*/  const),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int Indic_process_next_syllable (int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ ,unsigned int*,int,scalar_t__ (*) (int /*<<< orphan*/  const)) ; 
 int /*<<< orphan*/  TRACE (char*,int,...) ; 
 int /*<<< orphan*/  debug_output_string (int /*<<< orphan*/  const*,unsigned int,scalar_t__ (*) (int /*<<< orphan*/  const)) ; 
 TYPE_1__* heap_alloc (int) ; 
 scalar_t__ lex_Generic ; 

void Indic_ParseSyllables(HDC hdc, SCRIPT_ANALYSIS *psa, ScriptCache *psc, const WCHAR *input, unsigned int cChar,
        IndicSyllable **syllables, int *syllable_count, lexical_function lex, BOOL modern)
{
    unsigned int center = 0;
    int index = 0;
    int next = 0;

    *syllable_count = 0;

    if (!lex)
    {
        ERR("Failure to have required functions\n");
        return;
    }

    debug_output_string(input, cChar, lex);
    while (next != -1)
    {
        while((next < cChar) && lex(input[next]) == lex_Generic)
            next++;
        index = next;
        if (next >= cChar)
            break;
        next = Indic_process_next_syllable(input, cChar, 0, &center, index, lex);
        if (next != -1)
        {
            if (*syllable_count)
                *syllables = HeapReAlloc(GetProcessHeap(),0,*syllables, sizeof(IndicSyllable)*(*syllable_count+1));
            else
                *syllables = heap_alloc(sizeof(**syllables));
            (*syllables)[*syllable_count].start = index;
            (*syllables)[*syllable_count].base = center;
            (*syllables)[*syllable_count].ralf = -1;
            (*syllables)[*syllable_count].blwf = -1;
            (*syllables)[*syllable_count].pref = -1;
            (*syllables)[*syllable_count].end = next-1;
            FindBaseConsonant(hdc, psa, psc, input, &(*syllables)[*syllable_count], lex, modern);
            index = next;
            *syllable_count = (*syllable_count)+1;
        }
        else if (index < cChar)
        {
            TRACE("Processing failed at %i\n",index);
            next = ++index;
        }
    }
    TRACE("Processed %i of %i characters into %i syllables\n",index,cChar,*syllable_count);
}