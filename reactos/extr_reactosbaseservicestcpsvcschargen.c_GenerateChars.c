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
typedef  int /*<<< orphan*/  SOCKET ;
typedef  size_t INT ;
typedef  scalar_t__ CHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 size_t ASCII_END ; 
 size_t ASCII_START ; 
 int LINESIZE ; 
 int NUM_CHARS ; 
 int /*<<< orphan*/  SendLine (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bShutdown ; 

__attribute__((used)) static BOOL
GenerateChars(SOCKET sock)
{
    CHAR chars[NUM_CHARS];
    CHAR line[LINESIZE];
    INT charIndex;
    INT loopIndex;
    INT i;

    /* fill the array with printable characters */
    for (charIndex = 0, i = ASCII_START; i <= ASCII_END; charIndex++, i++)
        chars[charIndex] = (CHAR)i;

    loopIndex = 0;
    while (!bShutdown)
    {
        /* reset the loop when we hit the last char */
        if (loopIndex == NUM_CHARS)
            loopIndex = 0;

        /* fill a line array to send */
        charIndex = loopIndex;
        for (i=0; i < LINESIZE - 2; i++)
        {
            line[i] = chars[charIndex];

            /* if we hit the end char, reset it */
            if (chars[charIndex] == chars[NUM_CHARS - 1])
                charIndex = 0;
            else
                charIndex++;
        }
        line[LINESIZE - 2] = '\r';
        line[LINESIZE - 1] = '\n';

        if (!SendLine(sock, line))
            break;

        /* start printing from next char in the array */
        loopIndex++;
    }

    return TRUE;
}