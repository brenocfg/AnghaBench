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
typedef  int /*<<< orphan*/  VOID ;
typedef  size_t ULONG ;
typedef  char* PCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (char*) ; 

VOID UiEscapeString(PCHAR String)
{
    ULONG    Idx;

    for (Idx=0; Idx<strlen(String); Idx++)
    {
        // Escape the new line characters
        if (String[Idx] == '\\' && String[Idx+1] == 'n')
        {
            // Escape the character
            String[Idx] = '\n';

            // Move the rest of the string up
            strcpy(&String[Idx+1], &String[Idx+2]);
        }
    }
}