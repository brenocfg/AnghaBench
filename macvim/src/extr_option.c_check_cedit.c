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
typedef  int /*<<< orphan*/  char_u ;

/* Variables and functions */
 scalar_t__ NUL ; 
 int cedit_key ; 
 int /*<<< orphan*/ * e_invarg ; 
 scalar_t__* p_cedit ; 
 int string_to_key (scalar_t__*) ; 
 scalar_t__ vim_isprintc (int) ; 

__attribute__((used)) static char_u *
check_cedit()
{
    int n;

    if (*p_cedit == NUL)
	cedit_key = -1;
    else
    {
	n = string_to_key(p_cedit);
	if (vim_isprintc(n))
	    return e_invarg;
	cedit_key = n;
    }
    return NULL;
}