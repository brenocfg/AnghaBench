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
typedef  char* LPWSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL verify_format(LPWSTR data)
{
    int count = 0;

    while (*data)
    {
        if (*data == '[' && *(data - 1) != '\\')
            count++;
        else if (*data == ']')
            count--;

        data++;
    }

    if (count > 0)
        return FALSE;

    return TRUE;
}