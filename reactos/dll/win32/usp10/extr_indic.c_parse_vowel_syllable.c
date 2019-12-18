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
typedef  scalar_t__ (* lexical_function ) (int /*<<< orphan*/  const) ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 scalar_t__ is_consonant (scalar_t__) ; 
 scalar_t__ is_joiner (scalar_t__) ; 
 scalar_t__ is_matra (scalar_t__) ; 
 scalar_t__ lex_Halant ; 
 scalar_t__ lex_Modifier ; 
 scalar_t__ lex_Nukta ; 
 scalar_t__ lex_Vedic ; 
 scalar_t__ lex_ZWJ ; 

__attribute__((used)) static int parse_vowel_syllable(const WCHAR *input, unsigned int cChar,
        unsigned int start, unsigned int next, lexical_function lex)
{
    if ((next < cChar) && lex(input[next]) == lex_Nukta)
        next++;
    if ((next < cChar) && is_joiner( lex(input[next]) ) && lex(input[next+1])==lex_Halant && is_consonant( lex(input[next+2]) ))
        next+=3;
    else if ((next < cChar) && lex(input[next])==lex_Halant && is_consonant( lex(input[next+1]) ))
        next+=2;
    else if ((next < cChar) && lex(input[next])==lex_ZWJ && is_consonant( lex(input[next+1]) ))
        next+=2;

    if ((next < cChar) && is_matra( lex(input[next]) ))
    {
        while((next < cChar) && is_matra( lex(input[next]) ))
            next++;
        if ((next < cChar) && lex(input[next]) == lex_Nukta)
            next++;
        if ((next < cChar) && lex(input[next]) == lex_Halant)
            next++;
    }

    if ((next < cChar) && lex(input[next]) == lex_Modifier)
        next++;
    if ((next < cChar) && lex(input[next]) == lex_Vedic)
        next++;
    return next;
}