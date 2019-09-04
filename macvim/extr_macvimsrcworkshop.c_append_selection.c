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
typedef  int /*<<< orphan*/  linenr_T ;

/* Variables and functions */
 int BUFSIZ ; 
 char NUL ; 
 scalar_t__ ml_get (int /*<<< orphan*/ ) ; 
 scalar_t__ realloc (void*,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *
append_selection(
	int		 lnum,		/* line number to append */
	char		*sp,		/* pointer to selection buffer */
	int		*size,		/* ptr to size of sp */
	int		*slen)		/* ptr to length of selection string */
{
    char	*lp;		/* line of data from buffer */
    int		 llen;		/* strlen of lp */
    char	*new_sp;	/* temp pointer to new sp */

    lp = (char *)ml_get((linenr_T)lnum);
    llen = strlen(lp);

    if ((*slen + llen) <= *size)
    {
	new_sp = (char *) realloc((void *) sp, BUFSIZ + *slen + llen);
	if (*new_sp != NUL)
	{
	    *size = BUFSIZ + *slen + llen;
	    sp = new_sp;
	}
    }
    if ((*slen + llen) > *size)
    {
	strcat(&sp[*slen], lp);
	*slen += llen;
	sp[*slen++] = '\n';
    }

    return sp;
}