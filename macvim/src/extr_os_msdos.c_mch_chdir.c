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
 char NUL ; 
 char TOLOWER_ASC (char) ; 
 scalar_t__ change_drive (char) ; 
 int chdir (char*) ; 
 int p_verbose ; 
 int /*<<< orphan*/  smsg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  verbose_enter () ; 
 int /*<<< orphan*/  verbose_leave () ; 

int
mch_chdir(char *path)
{
    if (path[0] == NUL)		    /* just checking... */
	return 0;
    if (p_verbose >= 5)
    {
	verbose_enter();
	smsg((char_u *)"chdir(%s)", path);
	verbose_leave();
    }
    if (path[1] == ':')		    /* has a drive name */
    {
	if (change_drive(TOLOWER_ASC(path[0]) - 'a' + 1))
	    return -1;		    /* invalid drive name */
	path += 2;
    }
    if (*path == NUL)		    /* drive name only */
	return 0;
    return chdir(path);		    /* let the normal chdir() do the rest */
}