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
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WSDLEVEL (int) ; 
 int WS_TRACE ; 
 int WS_TRACE_VERBOSE ; 
 int /*<<< orphan*/  coloncmd (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vim_snprintf (char*,int,char*,int,int,int,char*) ; 
 int /*<<< orphan*/  wstrace (char*,char*,int,int,int) ; 

void
workshop_set_mark(
	char		*filename,	/* filename which gets the mark */
	int		 lineno,	/* line number which gets the mark */
	int		 markId,	/* unique mark identifier */
	int		 idx)		/* which mark to use */
{
    char	cbuf[BUFSIZ];	/* command buffer */

    /* Set mark in a given file */
#ifdef WSDEBUG_TRACE
    if (WSDLEVEL(WS_TRACE_VERBOSE | WS_TRACE))
	wstrace("workshop_set_mark(%s, %d (ln), %d (id), %d (idx))\n",
		filename, lineno, markId, idx);
#endif

    vim_snprintf(cbuf, sizeof(cbuf), "sign place %d line=%d name=%d file=%s",
					       markId, lineno, idx, filename);
    coloncmd(cbuf, TRUE);
}