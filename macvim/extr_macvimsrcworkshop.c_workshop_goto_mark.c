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
typedef  int /*<<< orphan*/  char_u ;
typedef  int /*<<< orphan*/  cbuf ;

/* Variables and functions */
 int BUFSIZ ; 
 char NUL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  coloncmd (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gui_mch_set_footer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vim_snprintf (char*,int,char*,int,char*) ; 

void
workshop_goto_mark(
	char		*filename,
	int		 markId,
	char		*message)
{
    char	cbuf[BUFSIZ];	/* command buffer */

    /* Goto mark */
#ifdef WSDEBUG_TRACE
    if (WSDLEVEL(WS_TRACE_VERBOSE | WS_TRACE))
	wstrace("workshop_goto_mark(%s, %d (id), %s)\n",
		filename, markId, message && *message &&
		!(*message == ' ' && message[1] == NULL) ?
		message : "<None>");
#endif

    vim_snprintf(cbuf, sizeof(cbuf), "sign jump %d file=%s", markId, filename);
    coloncmd(cbuf, TRUE);
    if (message != NULL && *message != NUL)
	gui_mch_set_footer((char_u *)message);
}