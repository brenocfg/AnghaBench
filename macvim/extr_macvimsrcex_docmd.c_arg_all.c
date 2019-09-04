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
 int ARGCOUNT ; 
 int /*<<< orphan*/ * ARGLIST ; 
 char NUL ; 
 char* alist_name (int /*<<< orphan*/ *) ; 
 char* alloc (unsigned int) ; 

__attribute__((used)) static char_u *
arg_all()
{
    int		len;
    int		idx;
    char_u	*retval = NULL;
    char_u	*p;

    /*
     * Do this loop two times:
     * first time: compute the total length
     * second time: concatenate the names
     */
    for (;;)
    {
	len = 0;
	for (idx = 0; idx < ARGCOUNT; ++idx)
	{
	    p = alist_name(&ARGLIST[idx]);
	    if (p != NULL)
	    {
		if (len > 0)
		{
		    /* insert a space in between names */
		    if (retval != NULL)
			retval[len] = ' ';
		    ++len;
		}
		for ( ; *p != NUL; ++p)
		{
		    if (*p == ' ' || *p == '\\')
		    {
			/* insert a backslash */
			if (retval != NULL)
			    retval[len] = '\\';
			++len;
		    }
		    if (retval != NULL)
			retval[len] = *p;
		    ++len;
		}
	    }
	}

	/* second time: break here */
	if (retval != NULL)
	{
	    retval[len] = NUL;
	    break;
	}

	/* allocate memory */
	retval = alloc((unsigned)len + 1);
	if (retval == NULL)
	    break;
    }

    return retval;
}