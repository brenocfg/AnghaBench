#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char char_u ;
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_4__ {scalar_t__ Y; scalar_t__ X; } ;
struct TYPE_3__ {scalar_t__ Bottom; int Left; scalar_t__ Top; scalar_t__ Right; } ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  Columns ; 
 char ESC ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MessageBeep (int) ; 
 char NUL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WaitForChar (scalar_t__) ; 
 int /*<<< orphan*/  clear_screen () ; 
 int /*<<< orphan*/  clear_to_end_of_display () ; 
 int /*<<< orphan*/  clear_to_end_of_line () ; 
 int /*<<< orphan*/  cursor_visible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_lines (int) ; 
 scalar_t__ fdDump ; 
 int /*<<< orphan*/  fflush (scalar_t__) ; 
 int /*<<< orphan*/  fputc (char,scalar_t__) ; 
 int /*<<< orphan*/  fputs (char*,scalar_t__) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,scalar_t__) ; 
 TYPE_2__ g_coord ; 
 TYPE_1__ g_srScrollRegion ; 
 int getdigits (char**) ; 
 int /*<<< orphan*/  gotoxy (int,int) ; 
 int /*<<< orphan*/  insert_lines (int) ; 
 int /*<<< orphan*/  max (scalar_t__,int) ; 
 int /*<<< orphan*/  min (scalar_t__,int) ; 
 int /*<<< orphan*/  normvideo () ; 
 scalar_t__ p_wd ; 
 int /*<<< orphan*/  scroll (int) ; 
 int /*<<< orphan*/  set_scroll_region (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  standend () ; 
 int /*<<< orphan*/  standout () ; 
 int /*<<< orphan*/  strcspn (char*,char*) ; 
 int /*<<< orphan*/  term_console ; 
 int /*<<< orphan*/  termcap_mode_end () ; 
 int /*<<< orphan*/  termcap_mode_start () ; 
 int /*<<< orphan*/  textattr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  textbackground (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  textcolor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  visual_bell () ; 
 int /*<<< orphan*/  write (int,char*,unsigned int) ; 
 int write_chars (char*,int) ; 

void
mch_write(
    char_u  *s,
    int	    len)
{
    s[len] = NUL;

    if (!term_console)
    {
	write(1, s, (unsigned)len);
	return;
    }

    /* translate ESC | sequences into faked bios calls */
    while (len--)
    {
	/* optimization: use one single write_chars for runs of text,
	 * rather than once per character  It ain't curses, but it helps. */
	DWORD  prefix = (DWORD)strcspn(s, "\n\r\b\a\033");

	if (p_wd)
	{
	    WaitForChar(p_wd);
	    if (prefix != 0)
		prefix = 1;
	}

	if (prefix != 0)
	{
	    DWORD nWritten;

	    nWritten = write_chars(s, prefix);
#ifdef MCH_WRITE_DUMP
	    if (fdDump)
	    {
		fputc('>', fdDump);
		fwrite(s, sizeof(char_u), nWritten, fdDump);
		fputs("<\n", fdDump);
	    }
#endif
	    len -= (nWritten - 1);
	    s += nWritten;
	}
	else if (s[0] == '\n')
	{
	    /* \n, newline: go to the beginning of the next line or scroll */
	    if (g_coord.Y == g_srScrollRegion.Bottom)
	    {
		scroll(1);
		gotoxy(g_srScrollRegion.Left + 1, g_srScrollRegion.Bottom + 1);
	    }
	    else
	    {
		gotoxy(g_srScrollRegion.Left + 1, g_coord.Y + 2);
	    }
#ifdef MCH_WRITE_DUMP
	    if (fdDump)
		fputs("\\n\n", fdDump);
#endif
	    s++;
	}
	else if (s[0] == '\r')
	{
	    /* \r, carriage return: go to beginning of line */
	    gotoxy(g_srScrollRegion.Left+1, g_coord.Y + 1);
#ifdef MCH_WRITE_DUMP
	    if (fdDump)
		fputs("\\r\n", fdDump);
#endif
	    s++;
	}
	else if (s[0] == '\b')
	{
	    /* \b, backspace: move cursor one position left */
	    if (g_coord.X > g_srScrollRegion.Left)
		g_coord.X--;
	    else if (g_coord.Y > g_srScrollRegion.Top)
	    {
		g_coord.X = g_srScrollRegion.Right;
		g_coord.Y--;
	    }
	    gotoxy(g_coord.X + 1, g_coord.Y + 1);
#ifdef MCH_WRITE_DUMP
	    if (fdDump)
		fputs("\\b\n", fdDump);
#endif
	    s++;
	}
	else if (s[0] == '\a')
	{
	    /* \a, bell */
	    MessageBeep(0xFFFFFFFF);
#ifdef MCH_WRITE_DUMP
	    if (fdDump)
		fputs("\\a\n", fdDump);
#endif
	    s++;
	}
	else if (s[0] == ESC && len >= 3-1 && s[1] == '|')
	{
#ifdef MCH_WRITE_DUMP
	    char_u  *old_s = s;
#endif
	    char_u  *p;
	    int	    arg1 = 0, arg2 = 0;

	    switch (s[2])
	    {
	    /* one or two numeric arguments, separated by ';' */

	    case '0': case '1': case '2': case '3': case '4':
	    case '5': case '6': case '7': case '8': case '9':
		p = s + 2;
		arg1 = getdigits(&p);	    /* no check for length! */
		if (p > s + len)
		    break;

		if (*p == ';')
		{
		    ++p;
		    arg2 = getdigits(&p);   /* no check for length! */
		    if (p > s + len)
			break;

		    if (*p == 'H')
			gotoxy(arg2, arg1);
		    else if (*p == 'r')
			set_scroll_region(0, arg1 - 1, Columns - 1, arg2 - 1);
		}
		else if (*p == 'A')
		{
		    /* move cursor up arg1 lines in same column */
		    gotoxy(g_coord.X + 1,
			   max(g_srScrollRegion.Top, g_coord.Y - arg1) + 1);
		}
		else if (*p == 'C')
		{
		    /* move cursor right arg1 columns in same line */
		    gotoxy(min(g_srScrollRegion.Right, g_coord.X + arg1) + 1,
			   g_coord.Y + 1);
		}
		else if (*p == 'H')
		{
		    gotoxy(1, arg1);
		}
		else if (*p == 'L')
		{
		    insert_lines(arg1);
		}
		else if (*p == 'm')
		{
		    if (arg1 == 0)
			normvideo();
		    else
			textattr((WORD) arg1);
		}
		else if (*p == 'f')
		{
		    textcolor((WORD) arg1);
		}
		else if (*p == 'b')
		{
		    textbackground((WORD) arg1);
		}
		else if (*p == 'M')
		{
		    delete_lines(arg1);
		}

		len -= (int)(p - s);
		s = p + 1;
		break;


	    /* Three-character escape sequences */

	    case 'A':
		/* move cursor up one line in same column */
		gotoxy(g_coord.X + 1,
		       max(g_srScrollRegion.Top, g_coord.Y - 1) + 1);
		goto got3;

	    case 'B':
		visual_bell();
		goto got3;

	    case 'C':
		/* move cursor right one column in same line */
		gotoxy(min(g_srScrollRegion.Right, g_coord.X + 1) + 1,
		       g_coord.Y + 1);
		goto got3;

	    case 'E':
		termcap_mode_end();
		goto got3;

	    case 'F':
		standout();
		goto got3;

	    case 'f':
		standend();
		goto got3;

	    case 'H':
		gotoxy(1, 1);
		goto got3;

	    case 'j':
		clear_to_end_of_display();
		goto got3;

	    case 'J':
		clear_screen();
		goto got3;

	    case 'K':
		clear_to_end_of_line();
		goto got3;

	    case 'L':
		insert_lines(1);
		goto got3;

	    case 'M':
		delete_lines(1);
		goto got3;

	    case 'S':
		termcap_mode_start();
		goto got3;

	    case 'V':
		cursor_visible(TRUE);
		goto got3;

	    case 'v':
		cursor_visible(FALSE);
		goto got3;

	    got3:
		s += 3;
		len -= 2;
	    }

#ifdef MCH_WRITE_DUMP
	    if (fdDump)
	    {
		fputs("ESC | ", fdDump);
		fwrite(old_s + 2, sizeof(char_u), s - old_s - 2, fdDump);
		fputc('\n', fdDump);
	    }
#endif
	}
	else
	{
	    /* Write a single character */
	    DWORD nWritten;

	    nWritten = write_chars(s, 1);
#ifdef MCH_WRITE_DUMP
	    if (fdDump)
	    {
		fputc('>', fdDump);
		fwrite(s, sizeof(char_u), nWritten, fdDump);
		fputs("<\n", fdDump);
	    }
#endif

	    len -= (nWritten - 1);
	    s += nWritten;
	}
    }

#ifdef MCH_WRITE_DUMP
    if (fdDump)
	fflush(fdDump);
#endif
}