#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int lnum; int col; } ;
typedef  TYPE_2__ pos_T ;
struct TYPE_6__ {char vi_mode; TYPE_2__ vi_end; TYPE_2__ vi_start; } ;
struct TYPE_8__ {TYPE_1__ b_visual; } ;
typedef  TYPE_3__ buf_T ;

/* Variables and functions */
 int BUFSIZ ; 
 char NUL ; 
 char* append_selection (int /*<<< orphan*/ ,char*,int*,int*) ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ ml_get (int) ; 
 scalar_t__ ml_get_pos (TYPE_2__*) ; 
 scalar_t__ realloc (char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static char *
get_selection(
	buf_T		*buf)		/* buffer whose selection we want */
{
    pos_T	*start;		/* start of the selection */
    pos_T	*end;		/* end of the selection */
    char	*lp;		/* pointer to actual line data */
    int		 llen;		/* length of actual line data */
    char	*sp;		/* pointer to selection  buffer */
    int		 slen;		/* string length in selection buffer */
    int		 size;		/* size of selection buffer */
    char	*new_sp;	/* temp pointer to new sp */
    int		 lnum;		/* line number we are appending */

    if (buf->b_visual.vi_mode == 'v')
    {
	start = &buf->b_visual.vi_start;
	end = &buf->b_visual.vi_end;
	if (start->lnum == end->lnum)
	{
	    /* selection is all on one line */
	    lp = (char *) ml_get_pos(start);
	    llen = end->col - start->col + 1;
	    sp = (char *) malloc(llen + 1);
	    if (sp != NULL)
	    {
		strncpy(sp, lp, llen);
		sp[llen] = NUL;
	    }
	}
	else
	{
	    /* multi-line selection */
	    lp = (char *) ml_get_pos(start);
	    llen = strlen(lp);
	    sp = (char *) malloc(BUFSIZ + llen);
	    if (sp != NULL)
	    {
		size = BUFSIZ + llen;
		strcpy(sp, lp);
		sp[llen] = '\n';
		slen = llen + 1;

		lnum = start->lnum + 1;
		while (lnum < end->lnum)
		    sp = append_selection(lnum++, sp, &size, &slen);

		lp = (char *) ml_get(end->lnum);
		llen = end->col + 1;
		if ((slen + llen) >= size)
		{
		    new_sp = (char *)
			realloc(sp, slen + llen + 1);
		    if (new_sp != NULL)
		    {
			size += llen + 1;
			sp = new_sp;
		    }
		}
		if ((slen + llen) < size)
		{
		    strncpy(&sp[slen], lp, llen);
		    sp[slen + llen] = NUL;
		}

	    }
	}
    }
    else
	sp = NULL;

    return sp;
}