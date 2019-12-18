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

/* Variables and functions */
 int /*<<< orphan*/  BUFSIZE ; 
 scalar_t__ NUL ; 
 scalar_t__* getenv (char*) ; 
 int /*<<< orphan*/  installdir ; 
 int /*<<< orphan*/  mch_chdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * my_fullpath (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  myexit (int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  putenv (char*) ; 
 int /*<<< orphan*/  remove_tail (int /*<<< orphan*/ ) ; 
 scalar_t__* sysdrive ; 

__attribute__((used)) static void
do_inits(char **argv)
{
#ifdef DJGPP
    /*
     * Use Long File Names by default, if $LFN not set.
     */
    if (getenv("LFN") == NULL)
	putenv("LFN=y");
#endif

    /* Find out the full path of our executable. */
    if (my_fullpath(installdir, argv[0], BUFSIZE) == NULL)
    {
	printf("ERROR: Cannot get name of executable\n");
	myexit(1);
    }
    /* remove the tail, the executable name "install.exe" */
    remove_tail(installdir);

    /* change to the installdir */
    mch_chdir(installdir);

    /* Find the system drive.  Only used for searching the Vim executable, not
     * very important. */
    sysdrive = getenv("SYSTEMDRIVE");
    if (sysdrive == NULL || *sysdrive == NUL)
	sysdrive = "C:\\";
}