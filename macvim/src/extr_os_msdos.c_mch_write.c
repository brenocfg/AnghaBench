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
 char ESC ; 
 int S_iBottom ; 
 int S_iCurrentColumn ; 
 int S_iLeft ; 
 int S_iRight ; 
 int S_iTop ; 
 int /*<<< orphan*/  ScreenVisualBell () ; 
 int /*<<< orphan*/  WaitForChar (scalar_t__) ; 
 scalar_t__ full_screen ; 
 int /*<<< orphan*/  myclreol () ; 
 int /*<<< orphan*/  myclrscr () ; 
 int /*<<< orphan*/  mydelline () ; 
 int /*<<< orphan*/  myflush () ; 
 int mygetdigits (char**) ; 
 int /*<<< orphan*/  mygotoxy (int,int) ; 
 int /*<<< orphan*/  myinsline () ; 
 int /*<<< orphan*/  mynormvideo () ; 
 int /*<<< orphan*/  myputch (char) ; 
 int /*<<< orphan*/  mytextattr (int) ; 
 int /*<<< orphan*/  mytextbackground (int) ; 
 int /*<<< orphan*/  mytextcolor (int) ; 
 int /*<<< orphan*/  mywindow (int,int,int,int) ; 
 scalar_t__ p_wd ; 
 scalar_t__ term_console ; 
 int /*<<< orphan*/  write (int,char*,unsigned int) ; 

void
mch_write(
    char_u	*s,
    int		len)
{
    char_u	*p;
    int		row, col;

    if (term_console && full_screen)
	while (len--)
	{
	    /* translate ESC | sequences into bios calls */
	    if (p_wd)	    /* testing: wait a bit for each char */
		WaitForChar(p_wd);

	    if (s[0] == '\n')
#ifdef DJGPP
	    {
		myflush();
		S_iCurrentColumn = S_iLeft - 1;
	    }
#else
		myputch('\r');
#endif
	    else if (s[0] == ESC && len > 1 && s[1] == '|')
	    {
		switch (s[2])
		{
#ifdef DJGPP
		case 'B':   ScreenVisualBell();
			    goto got3;
#endif
		case 'J':
#ifdef DJGPP
			    myflush();
#endif
			    myclrscr();
			    goto got3;

		case 'K':
#ifdef DJGPP
			    myflush();
#endif
			    myclreol();
			    goto got3;

		case 'L':
#ifdef DJGPP
			    myflush();
#endif
			    myinsline();
			    goto got3;

		case 'M':
#ifdef DJGPP
			    myflush();
#endif
			    mydelline();
got3:			    s += 3;
			    len -= 2;
			    continue;

		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':   p = s + 2;
			    row = mygetdigits(&p);    /* no check for length! */
			    if (p > s + len)
				break;
			    if (*p == ';')
			    {
				++p;
				col = mygetdigits(&p); /* no check for length! */
				if (p > s + len)
				    break;
				if (*p == 'H' || *p == 'r' || *p == 'V')
				{
#ifdef DJGPP
				    myflush();
#endif
				    if (*p == 'H')  /* set cursor position */
					mygotoxy(col, row);
				    else if (*p == 'V')
					mywindow(row, S_iTop, col, S_iBottom);
				    else	    /* set scroll region  */
					mywindow(S_iLeft, row, S_iRight, col);
				    len -= p - s;
				    s = p + 1;
				    continue;
				}
			    }
			    else if (*p == 'm' || *p == 'f' || *p == 'b')
			    {
				if (*p == 'm')	    /* set color */
				{
				    if (row == 0)
					mynormvideo();/* reset color */
				    else
					mytextattr(row);
				}
				else if (*p == 'f') /* set foreground color */
				    mytextcolor(row);
				else		    /* set background color */
				    mytextbackground(row);

				len -= p - s;
				s = p + 1;
				continue;
			    }
		}
	    }
	    myputch(*s++);
	}
    else
    {
	write(1, s, (unsigned)len);
    }
}