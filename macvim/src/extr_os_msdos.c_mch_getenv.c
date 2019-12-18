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
 int MAXENVLEN ; 
 scalar_t__ NUL ; 
 int STRLEN (scalar_t__*) ; 
 scalar_t__* alloc (int) ; 
 scalar_t__ getenv (char*) ; 
 scalar_t__ toupper (scalar_t__) ; 
 int /*<<< orphan*/  vim_free (scalar_t__*) ; 

char_u *
mch_getenv(char_u *name)
{
    int		i;
#define MAXENVLEN 50
    char_u	var_copy[MAXENVLEN + 1];
    char_u	*p;
    char_u	*res;

    /*
     * Take a copy of the argument, and force it to upper case before passing
     * to getenv().  On DOS systems, getenv() doesn't like lower-case argument
     * (unlike Win32 et al.)  If the name is too long to fit in var_copy[]
     * allocate memory.
     */
    if ((i = STRLEN(name)) > MAXENVLEN)
	p = alloc(i + 1);
    else
	p = var_copy;
    if (p == NULL)
	p = name;   /* out of memory, fall back to unmodified name */
    else
    {
	for (i = 0; name[i] != NUL; ++i)
	    p[i] = toupper(name[i]);
	p[i] = NUL;
    }

    res = (char_u *)getenv((char *)p);

    if (p != var_copy && p != name)
	vim_free(p);

    return res;
}