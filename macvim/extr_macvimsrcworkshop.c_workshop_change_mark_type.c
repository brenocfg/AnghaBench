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
 int /*<<< orphan*/  coloncmd (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vim_snprintf (char*,int,char*,int,int,char*) ; 

void
workshop_change_mark_type(
	char		*filename,	/* filename which gets the mark */
	int		 markId,	/* unique mark identifier */
	int		 idx)		/* which mark to use */
{
    char	cbuf[BUFSIZ];	/* command buffer */

    /* Change mark type */
#ifdef WSDEBUG_TRACE
    if (WSDLEVEL(WS_TRACE_VERBOSE | WS_TRACE))
	wstrace("workshop_change_mark_type(%s, %d, %d)\n",
		filename, markId, idx);
#endif

    vim_snprintf(cbuf, sizeof(cbuf),
		      "sign place %d name=%d file=%s", markId, idx, filename);
    coloncmd(cbuf, TRUE);
}