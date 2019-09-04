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
typedef  int /*<<< orphan*/  args_vector ;
typedef  int* LPWSTR ;
typedef  int INT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ InterpretCmd (int,int**) ; 
 int MAX_ARGS_COUNT ; 
 scalar_t__ TRUE ; 
 scalar_t__ iswspace (int) ; 
 int /*<<< orphan*/  memset (int**,int /*<<< orphan*/ ,int) ; 

BOOL
InterpretScript(LPWSTR input_line)
{
    LPWSTR args_vector[MAX_ARGS_COUNT];
    INT args_count = 0;
    BOOL bWhiteSpace = TRUE;
    LPWSTR ptr;

    memset(args_vector, 0, sizeof(args_vector));

    ptr = input_line;
    while (*ptr != 0)
    {
        if (iswspace(*ptr) || *ptr == L'\n')
        {
            *ptr = 0;
            bWhiteSpace = TRUE;
        }
        else
        {
            if ((bWhiteSpace != FALSE) && (args_count < MAX_ARGS_COUNT))
            {
                args_vector[args_count] = ptr;
                args_count++;
            }

            bWhiteSpace = FALSE;
        }

        ptr++;
    }

    /* sends the string to find the command */
    return InterpretCmd(args_count, args_vector);
}