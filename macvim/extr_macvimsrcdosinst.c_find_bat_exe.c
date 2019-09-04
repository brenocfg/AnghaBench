#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * oldbat; int /*<<< orphan*/  exename; void* oldexe; int /*<<< orphan*/  batname; } ;

/* Variables and functions */
 int TARGET_COUNT ; 
 int /*<<< orphan*/ * alloc (scalar_t__) ; 
 int /*<<< orphan*/ * default_bat_dir ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 char* installdir ; 
 int /*<<< orphan*/  mch_chdir (char*) ; 
 int /*<<< orphan*/  remove_tail (int /*<<< orphan*/ *) ; 
 void* searchpath_save (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (int /*<<< orphan*/ *) ; 
 char* sysdrive ; 
 TYPE_1__* targets ; 

__attribute__((used)) static void
find_bat_exe(int check_bat_only)
{
    int		i;

    /* avoid looking in the "installdir" by chdir to system root */
    mch_chdir(sysdrive);
    mch_chdir("\\");

    for (i = 1; i < TARGET_COUNT; ++i)
    {
	targets[i].oldbat = searchpath_save(targets[i].batname);
	if (!check_bat_only)
	    targets[i].oldexe = searchpath_save(targets[i].exename);

	if (default_bat_dir == NULL && targets[i].oldbat != NULL)
	{
	    default_bat_dir = alloc(strlen(targets[i].oldbat) + 1);
	    strcpy(default_bat_dir, targets[i].oldbat);
	    remove_tail(default_bat_dir);
	}
	if (check_bat_only && targets[i].oldbat != NULL)
	{
	    free(targets[i].oldbat);
	    targets[i].oldbat = NULL;
	}
    }

    mch_chdir(installdir);
}