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
typedef  size_t ULONG ;
typedef  char* PCHAR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN IniIsSectionName(PCHAR LineOfText, ULONG TextLength)
{
    ULONG        Idx;

    // Check the first character (skipping whitespace)
    // and make sure that it is an opening bracket
    for (Idx=0; Idx<TextLength; Idx++)
    {
        if ((LineOfText[Idx] == ' ') ||
            (LineOfText[Idx] == '\t'))
        {
            continue;
        }
        else if (LineOfText[Idx] == '[')
        {
            return TRUE;
        }
        else
        {
            break;
        }
    }

    return FALSE;
}