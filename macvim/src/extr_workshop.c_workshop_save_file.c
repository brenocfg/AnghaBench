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
 int /*<<< orphan*/  vim_snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  wstrace (char*,char*) ; 

void
workshop_save_file(
	    char	*filename)
{
    char	 cbuf[BUFSIZ];		/* build vim command here */

#ifdef WSDEBUG_TRACE
    if (WSDLEVEL(WS_TRACE_VERBOSE | WS_TRACE))
	wstrace("workshop_save_file(%s)\n", filename);
#endif

    /* Save the given file */
    vim_snprintf(cbuf, sizeof(cbuf), "w %s", filename);
    coloncmd(cbuf, TRUE);
}