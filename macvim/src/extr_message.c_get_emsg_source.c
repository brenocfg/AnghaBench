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
 scalar_t__ other_sourcing_name () ; 
 int /*<<< orphan*/ * sourcing_name ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char_u *
get_emsg_source()
{
    char_u	*Buf, *p;

    if (sourcing_name != NULL && other_sourcing_name())
    {
	p = (char_u *)_("Error detected while processing %s:");
	Buf = alloc((unsigned)(STRLEN(sourcing_name) + STRLEN(p)));
	if (Buf != NULL)
	    sprintf((char *)Buf, (char *)p, sourcing_name);
	return Buf;
    }
    return NULL;
}