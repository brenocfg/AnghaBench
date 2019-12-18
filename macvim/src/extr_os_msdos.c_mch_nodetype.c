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
typedef  scalar_t__ char_u ;

/* Variables and functions */
 int NODE_NORMAL ; 
 int NODE_WRITABLE ; 
 scalar_t__ NUL ; 
 scalar_t__ STRICMP (scalar_t__*,char*) ; 
 scalar_t__ STRNICMP (scalar_t__*,char*,int) ; 
 scalar_t__ VIM_ISDIGIT (scalar_t__) ; 

int
mch_nodetype(char_u *name)
{
    if (STRICMP(name, "AUX") == 0
	    || STRICMP(name, "CON") == 0
	    || STRICMP(name, "CLOCK$") == 0
	    || STRICMP(name, "NUL") == 0
	    || STRICMP(name, "PRN") == 0
	    || ((STRNICMP(name, "COM", 3) == 0
		    || STRNICMP(name, "LPT", 3) == 0)
		&& VIM_ISDIGIT(name[3])
		&& name[4] == NUL))
	return NODE_WRITABLE;
    /* TODO: NODE_OTHER? */
    return NODE_NORMAL;
}