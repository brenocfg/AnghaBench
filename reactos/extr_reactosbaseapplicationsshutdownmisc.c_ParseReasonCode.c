#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int major; int minor; int /*<<< orphan*/  flag; scalar_t__ prefix; } ;
typedef  TYPE_1__* PREASON ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int* LPCWSTR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ _wcsicmp (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  defaultReason ; 
 TYPE_1__* shutdownReason ; 
 scalar_t__ wcslen (int*) ; 

DWORD ParseReasonCode(LPCWSTR code)
{
    PREASON reasonptr;
    int majorCode = 0;
    int minorCode = 0;
    LPWSTR tmpPrefix = NULL;
    size_t codeSize;

    /* If no reason code is specified, use "Other (Unplanned)" as the default option */
    if(code == NULL)
    {
        return defaultReason;
    }
    else
    {
        /* Store the size of the code so we can use it later */
        codeSize = (size_t)wcslen(code);

        /* A colon cannot be the first or last character in the reason code */
        if ((code[0] == L':') || (code[codeSize] == L':'))
        {
            return defaultReason;
        }

        /* The minimum length that a reason code can be is 5-7 characters in length */
        if ((codeSize < 5) || (codeSize > 7))
        {
            return defaultReason;
        }

        /* TODO: Add code for reason parsing here. */

        /* Make sure that the major and minor codes are within size limits */
        if ((majorCode > 7 ) || (majorCode < 0) ||
            (minorCode > 20) || (minorCode < 0))
        {
            return defaultReason;
        }

        /* Figure out what flags to return */
        for (reasonptr = shutdownReason ; reasonptr->prefix ; reasonptr++)
        {
            if ((majorCode == reasonptr->major) &&
                (minorCode == reasonptr->minor) &&
                (_wcsicmp(tmpPrefix, reasonptr->prefix) != 0))
            {
                return reasonptr->flag;
            }
        }
    }

    return defaultReason;
}