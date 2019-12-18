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
typedef  char char_u ;

/* Variables and functions */
 int /*<<< orphan*/  mb_ptr_adv (char*) ; 
 char psepc ; 
 char psepcN ; 

void
slash_adjust(char_u *p)
{
#ifdef OLD_DJGPP    /* this seems to have been fixed in DJGPP 2.01 */
    /* DJGPP can't handle a file name that starts with a backslash, and when it
     * starts with a slash there should be no backslashes */
    if (*p == '\\' || *p == '/')
	while (*p)
	{
	    if (*p == '\\')
		*p = '/';
	    mb_ptr_adv(p);
	}
    else
#endif
    while (*p)
    {
	if (*p == psepcN)
	    *p = psepc;
	mb_ptr_adv(p);
    }
}