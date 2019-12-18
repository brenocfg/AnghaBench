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
 scalar_t__ lex_Halant ; 
 scalar_t__ lex_NBSP ; 
 scalar_t__ lex_Ra ; 
 scalar_t__ lex_Vowel ; 
 int parse_consonant_syllable (int /*<<< orphan*/  const*,unsigned int,unsigned int,unsigned int*,unsigned int,scalar_t__ (*) (int /*<<< orphan*/  const)) ; 
 int parse_vowel_syllable (int /*<<< orphan*/  const*,unsigned int,unsigned int,unsigned int,scalar_t__ (*) (int /*<<< orphan*/  const)) ; 

__attribute__((used)) static int Indic_process_next_syllable(const WCHAR *input, unsigned int cChar,
        unsigned int start, unsigned int *main, unsigned int next, lexical_function lex)
{
    if (lex(input[next])==lex_Vowel)
    {
        *main = next;
        return parse_vowel_syllable(input, cChar, start, next+1, lex);
    }
    else if ((cChar > next+3) && lex(input[next]) == lex_Ra && lex(input[next+1]) == lex_Halant && lex(input[next+2]) == lex_Vowel)
    {
        *main = next+2;
        return parse_vowel_syllable(input, cChar, start, next+3, lex);
    }

    else if (start == next && lex(input[next])==lex_NBSP)
    {
        *main = next;
        return parse_vowel_syllable(input, cChar, start, next+1, lex);
    }
    else if (start == next && (cChar > next+3) && lex(input[next]) == lex_Ra && lex(input[next+1]) == lex_Halant && lex(input[next+2]) == lex_NBSP)
    {
        *main = next+2;
        return parse_vowel_syllable(input, cChar, start, next+3, lex);
    }

    return parse_consonant_syllable(input, cChar, start, main, next, lex);
}