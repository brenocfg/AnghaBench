#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  char char_u ;
struct TYPE_2__ {char* w_p_briopt; int w_p_brishift; long w_p_brimin; int w_p_brisbr; } ;

/* Variables and functions */
 int FAIL ; 
 int FALSE ; 
 char NUL ; 
 int OK ; 
 scalar_t__ STRNCMP (char*,char*,int) ; 
 int TRUE ; 
 scalar_t__ VIM_ISDIGIT (char) ; 
 TYPE_1__* curwin ; 
 void* getdigits (char**) ; 

int
briopt_check()
{
    char_u	*p;
    int		bri_shift = 0;
    long	bri_min = 20;
    int		bri_sbr = FALSE;

    p = curwin->w_p_briopt;
    while (*p != NUL)
    {
	if (STRNCMP(p, "shift:", 6) == 0
		 && ((p[6] == '-' && VIM_ISDIGIT(p[7])) || VIM_ISDIGIT(p[6])))
	{
	    p += 6;
	    bri_shift = getdigits(&p);
	}
	else if (STRNCMP(p, "min:", 4) == 0 && VIM_ISDIGIT(p[4]))
	{
	    p += 4;
	    bri_min = getdigits(&p);
	}
	else if (STRNCMP(p, "sbr", 3) == 0)
	{
	    p += 3;
	    bri_sbr = TRUE;
	}
	if (*p != ',' && *p != NUL)
	    return FAIL;
	if (*p == ',')
	    ++p;
    }

    curwin->w_p_brishift = bri_shift;
    curwin->w_p_brimin   = bri_min;
    curwin->w_p_brisbr   = bri_sbr;

    return OK;
}