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

/* Variables and functions */
 scalar_t__ STRLEN (int /*<<< orphan*/ *) ; 
 scalar_t__ _ (char*) ; 
 int /*<<< orphan*/ * alloc (unsigned int) ; 
 scalar_t__ last_sourcing_lnum ; 
 scalar_t__ other_sourcing_name () ; 
 scalar_t__ sourcing_lnum ; 
 int /*<<< orphan*/ * sourcing_name ; 
 int /*<<< orphan*/  sprintf (char*,char*,long) ; 

__attribute__((used)) static char_u *
get_emsg_lnum()
{
    char_u	*Buf, *p;

    /* lnum is 0 when executing a command from the command line
     * argument, we don't want a line number then */
    if (sourcing_name != NULL
	    && (other_sourcing_name() || sourcing_lnum != last_sourcing_lnum)
	    && sourcing_lnum != 0)
    {
	p = (char_u *)_("line %4ld:");
	Buf = alloc((unsigned)(STRLEN(p) + 20));
	if (Buf != NULL)
	    sprintf((char *)Buf, (char *)p, (long)sourcing_lnum);
	return Buf;
    }
    return NULL;
}