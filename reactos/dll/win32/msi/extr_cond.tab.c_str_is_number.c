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
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  isdigitW (int /*<<< orphan*/ ) ; 
 int lstrlenW (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL str_is_number( LPCWSTR str )
{
    int i;

    if (!*str)
        return FALSE;

    for (i = 0; i < lstrlenW( str ); i++)
        if (!isdigitW(str[i]))
            return FALSE;

    return TRUE;
}