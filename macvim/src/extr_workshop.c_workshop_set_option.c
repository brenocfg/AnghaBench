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
 char NUL ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WSDLEVEL (int) ; 
 int WS_TRACE ; 
 int WS_TRACE_VERBOSE ; 
 int /*<<< orphan*/  coloncmd (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  vim_snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  wsdebug (char*) ; 
 int /*<<< orphan*/  wstrace (char*,char*,char*) ; 

void
workshop_set_option(
	char	*option,		/* name of a supported option */
	char	*value)			/* value to set option to */
{
    char	 cbuf[BUFSIZ];		/* command buffer */

#ifdef WSDEBUG_TRACE
    if (WSDLEVEL(WS_TRACE_VERBOSE | WS_TRACE))
    {
	wstrace("workshop_set_option(%s, %s)\n", option, value);
    }
#endif

    cbuf[0] = NUL;
    switch (*option)		/* switch on 1st letter */
    {
	case 's':
	    if (strcmp(option, "syntax") == 0)
		vim_snprintf(cbuf, sizeof(cbuf), "syntax %s", value);
	    else if (strcmp(option, "savefiles") == 0)
	    {
		/* XXX - Not yet implemented */
	    }
	    break;

	case 'l':
	    if (strcmp(option, "lineno") == 0)
		sprintf(cbuf, "set %snu",
			(strcmp(value, "on") == 0) ? "" : "no");
	    break;

	case 'p':
	    if (strcmp(option, "parentheses") == 0)
		sprintf(cbuf, "set %ssm",
			(strcmp(value, "on") == 0) ? "" : "no");
	    break;

	case 'w':
	    /* this option is set by a direct call */
#ifdef WSDEBUG
	    wsdebug("workshop_set_option: "
		    "Got unexpected workshopkeys option");
#endif
	    break;

	case 'b':	/* these options are set from direct calls */
	    if (option[7] == NUL && strcmp(option, "balloon") == 0)
	    {
#ifdef WSDEBUG
		/* set by direct call to workshop_balloon_mode */
		wsdebug("workshop_set_option: "
			"Got unexpected ballooneval option");
#endif
	    }
	    else if (strcmp(option, "balloondelay") == 0)
	    {
#ifdef WSDEBUG
		/* set by direct call to workshop_balloon_delay */
		wsdebug("workshop_set_option: "
			"Got unexpected balloondelay option");
#endif
	    }
	    break;
    }
    if (cbuf[0] != NUL)
	coloncmd(cbuf, TRUE);
}