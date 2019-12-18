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
typedef  int /*<<< orphan*/  cbuf ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  False ; 
 char NUL ; 
 int /*<<< orphan*/  coloncmd (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  vim_snprintf (char*,int,char*,char*,char*) ; 

__attribute__((used)) static void
load_buffer_by_name(
	char	*filename,		/* the file to load */
	int	 lnum)			/* an optional line number (or 0) */
{
    char	 lnumbuf[16];		/* make line number option for :e */
    char	 cbuf[BUFSIZ];		/* command buffer */

    if (lnum > 0)
	sprintf(lnumbuf, "+%d", lnum);
    else
	lnumbuf[0] = NUL;

    vim_snprintf(cbuf, sizeof(cbuf), "e %s %s", lnumbuf, filename);
    coloncmd(cbuf, False);
}