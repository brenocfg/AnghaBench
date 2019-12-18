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
 int FAIL ; 
 int MAXPATHL ; 
 scalar_t__ NUL ; 
 int OK ; 
 void* SPS_BEST ; 
 int SPS_DOUBLE ; 
 int SPS_FAST ; 
 scalar_t__ STRCMP (scalar_t__*,char*) ; 
 scalar_t__ STRNCMP (scalar_t__*,char*,int) ; 
 scalar_t__ VIM_ISDIGIT (scalar_t__) ; 
 int /*<<< orphan*/  copy_option_part (scalar_t__**,scalar_t__*,int,char*) ; 
 int getdigits (scalar_t__**) ; 
 scalar_t__* p_sps ; 
 int sps_flags ; 
 int sps_limit ; 

int
spell_check_sps()
{
    char_u	*p;
    char_u	*s;
    char_u	buf[MAXPATHL];
    int		f;

    sps_flags = 0;
    sps_limit = 9999;

    for (p = p_sps; *p != NUL; )
    {
	copy_option_part(&p, buf, MAXPATHL, ",");

	f = 0;
	if (VIM_ISDIGIT(*buf))
	{
	    s = buf;
	    sps_limit = getdigits(&s);
	    if (*s != NUL && !VIM_ISDIGIT(*s))
		f = -1;
	}
	else if (STRCMP(buf, "best") == 0)
	    f = SPS_BEST;
	else if (STRCMP(buf, "fast") == 0)
	    f = SPS_FAST;
	else if (STRCMP(buf, "double") == 0)
	    f = SPS_DOUBLE;
	else if (STRNCMP(buf, "expr:", 5) != 0
		&& STRNCMP(buf, "file:", 5) != 0)
	    f = -1;

	if (f == -1 || (sps_flags != 0 && f != 0))
	{
	    sps_flags = SPS_BEST;
	    sps_limit = 9999;
	    return FAIL;
	}
	if (f != 0)
	    sps_flags = f;
    }

    if (sps_flags == 0)
	sps_flags = SPS_BEST;

    return OK;
}