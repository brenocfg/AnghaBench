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
typedef  scalar_t__ char_u ;

/* Variables and functions */
 scalar_t__ NUL ; 
 scalar_t__* gettail (scalar_t__*) ; 
 int /*<<< orphan*/  mb_ptr_adv (scalar_t__*) ; 
 scalar_t__* p_sh ; 
 scalar_t__* skiptowhite (scalar_t__*) ; 
 scalar_t__ vim_ispathsep (scalar_t__) ; 
 scalar_t__* vim_strnsave (scalar_t__*,int) ; 
 scalar_t__* vim_strsave (scalar_t__*) ; 

char_u *
get_isolated_shell_name()
{
    char_u *p;

#ifdef WIN3264
    p = gettail(p_sh);
    p = vim_strnsave(p, (int)(skiptowhite(p) - p));
#else
    p = skiptowhite(p_sh);
    if (*p == NUL)
    {
	/* No white space, use the tail. */
	p = vim_strsave(gettail(p_sh));
    }
    else
    {
	char_u  *p1, *p2;

	/* Find the last path separator before the space. */
	p1 = p_sh;
	for (p2 = p_sh; p2 < p; mb_ptr_adv(p2))
	    if (vim_ispathsep(*p2))
		p1 = p2 + 1;
	p = vim_strnsave(p1, (int)(p - p1));
    }
#endif
    return p;
}