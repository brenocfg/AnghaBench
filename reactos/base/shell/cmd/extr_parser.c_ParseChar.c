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
typedef  scalar_t__ TCHAR ;

/* Variables and functions */
 scalar_t__ CurChar ; 
 scalar_t__* ParseLine ; 
 scalar_t__* ParsePos ; 
 int /*<<< orphan*/  ReadLine (scalar_t__*,scalar_t__) ; 
 scalar_t__ TRUE ; 
 scalar_t__ _T (char) ; 
 scalar_t__ bLineContinuations ; 
 scalar_t__ bParseError ; 

__attribute__((used)) static TCHAR ParseChar(void)
{
    TCHAR Char;

    if (bParseError)
        return (CurChar = 0);

restart:
    /*
     * Although CRs can be injected into a line via an environment
     * variable substitution, the parser ignores them - they won't
     * even separate tokens.
     */
    do
    {
        Char = *ParsePos++;
    }
    while (Char == _T('\r'));

    if (!Char)
    {
        ParsePos--;
        if (bLineContinuations)
        {
            if (!ReadLine(ParseLine, TRUE))
            {
                /* ^C pressed, or line was too long */
                bParseError = TRUE;
            }
            else if (*(ParsePos = ParseLine))
            {
                goto restart;
            }
        }
    }
    return (CurChar = Char);
}