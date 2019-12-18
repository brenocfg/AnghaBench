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
typedef  int /*<<< orphan*/  names ;
typedef  int /*<<< orphan*/  char_u ;

/* Variables and functions */
#define  BW40 133 
#define  BW80 132 
#define  C40 131 
#define  C4350 130 
#define  C80 129 
 int /*<<< orphan*/  EMSG (char*) ; 
 int FAIL ; 
#define  MONO 128 
 int OK ; 
 int /*<<< orphan*/  T_ME ; 
 scalar_t__ VIM_ISDIGIT (int /*<<< orphan*/ ) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  get_screenbase () ; 
 int mouse_x_div ; 
 int mouse_y_div ; 
 int /*<<< orphan*/  out_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shell_resized () ; 
 scalar_t__ stricmp (char*,char*) ; 
 int /*<<< orphan*/  textmode (int) ; 

int
mch_screenmode(char_u *arg)
{
    int		    mode;
    int		    i;
    static char	   *(names[]) = {"BW40", "C40", "BW80", "C80", "MONO", "C4350"};
    static int	    modes[]   = { BW40,	  C40,	 BW80,	 C80,	MONO,	C4350};

    mode = -1;
    if (VIM_ISDIGIT(*arg))		    /* mode number given */
	mode = atoi((char *)arg);
    else
    {
	for (i = 0; i < sizeof(names) / sizeof(char_u *); ++i)
	    if (stricmp(names[i], (char *)arg) == 0)
	    {
		mode = modes[i];
		break;
	    }
    }
    if (mode == -1)
    {
	EMSG("E362: Unsupported screen mode");
	return FAIL;
    }
    textmode(mode);		    /* use Borland function */
#ifdef DJGPP
    /* base address may have changed */
    get_screenbase();
#endif

    /* Screen colors may have changed. */
    out_str(T_ME);

#ifdef FEAT_MOUSE
    if (mode <= 1 || mode == 4 || mode == 5 || mode == 13 || mode == 0x13)
	mouse_x_div = 16;
    else
	mouse_x_div = 8;
    if (mode == 0x11 || mode == 0x12)
	mouse_y_div = 16;
    else if (mode == 0x10)
	mouse_y_div = 14;
    else
	mouse_y_div = 8;
    shell_resized();
#endif
    return OK;
}