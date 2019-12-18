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
typedef  int mode_t ;

/* Variables and functions */
 int S_ISGID ; 
 int S_ISUID ; 
 int S_ISVTX ; 
 char get_fileind (int) ; 
 int /*<<< orphan*/  xstrlcpy (char*,char const* const,int) ; 

__attribute__((used)) static char *get_lsperms(mode_t mode)
{
	static const char * const rwx[] = {"---", "--x", "-w-", "-wx", "r--", "r-x", "rw-", "rwx"};
	static char bits[11] = {'\0'};

	bits[0] = get_fileind(mode);
	xstrlcpy(&bits[1], rwx[(mode >> 6) & 7], 4);
	xstrlcpy(&bits[4], rwx[(mode >> 3) & 7], 4);
	xstrlcpy(&bits[7], rwx[(mode & 7)], 4);

	if (mode & S_ISUID)
		bits[3] = (mode & 0100) ? 's' : 'S';  /* user executable */
	if (mode & S_ISGID)
		bits[6] = (mode & 0010) ? 's' : 'l';  /* group executable */
	if (mode & S_ISVTX)
		bits[9] = (mode & 0001) ? 't' : 'T';  /* others executable */

	return bits;
}