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
typedef  int* LPWORD ;
typedef  int* LPTSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int _T (int /*<<< orphan*/ ) ; 
 scalar_t__ _istdigit (int) ; 

__attribute__((used)) static BOOL
ReadNumber (LPTSTR *s, LPWORD lpwValue)
{
    if (_istdigit (**s))
    {
        while (_istdigit (**s))
        {
            *lpwValue = *lpwValue * 10 + **s - _T('0');
            (*s)++;
        }
        return TRUE;
    }
    return FALSE;
}