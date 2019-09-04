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
typedef  scalar_t__ Boolean ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  coloncmd (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

void
workshop_balloon_mode(
	Boolean	 on)
{
    char	 cbuf[BUFSIZ];		/* command buffer */

#ifdef WSDEBUG_TRACE
    if (WSDLEVEL(WS_TRACE_VERBOSE | WS_TRACE))
	wstrace("workshop_balloon_mode(%s)\n", on ? "True" : "False");
#endif

    sprintf(cbuf, "set %sbeval", on ? "" : "no");
    coloncmd(cbuf, TRUE);
}