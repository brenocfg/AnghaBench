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
 int consonant_header (int /*<<< orphan*/  const*,unsigned int,unsigned int,unsigned int,scalar_t__ (*) (int /*<<< orphan*/  const)) ; 
 scalar_t__ is_consonant (scalar_t__) ; 
 scalar_t__ is_joiner (scalar_t__) ; 
 scalar_t__ is_matra (scalar_t__) ; 
 scalar_t__ lex_Anudatta ; 
 scalar_t__ lex_Halant ; 
 scalar_t__ lex_Modifier ; 
 scalar_t__ lex_Nukta ; 
 scalar_t__ lex_Vedic ; 

__attribute__((used)) static int parse_consonant_syllable(const WCHAR *input, unsigned int cChar,
        unsigned int start, unsigned int *main, unsigned int next, lexical_function lex)
{
    int check;
    int headers = 0;
    do
    {
        check = consonant_header(input,cChar,start,next,lex);
        if (check != -1)
        {
            next = check;
            headers++;
        }
    } while (check != -1);
    if (headers || is_consonant( lex(input[next]) ))
    {
        *main = next;
        next++;
    }
    else
        return -1;
    if ((next < cChar) && lex(input[next]) == lex_Nukta)
            next++;
    if ((next < cChar) && lex(input[next]) == lex_Anudatta)
            next++;

    if ((next < cChar) && lex(input[next]) == lex_Halant)
    {
        next++;
        if((next < cChar) && is_joiner( lex(input[next]) ))
            next++;
    }
    else if (next < cChar)
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