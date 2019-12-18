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
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 scalar_t__ EOVERFLOW ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 char* emalloc (size_t) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static bool
itsdir(char const *name)
{
	struct stat st;
	int			res = stat(name, &st);
#ifdef S_ISDIR
	if (res == 0)
		return S_ISDIR(st.st_mode) != 0;
#endif
	if (res == 0 || errno == EOVERFLOW)
	{
		size_t		n = strlen(name);
		char	   *nameslashdot = emalloc(n + 3);
		bool		dir;

		memcpy(nameslashdot, name, n);
		strcpy(&nameslashdot[n], &"/."[!(n && name[n - 1] != '/')]);
		dir = stat(nameslashdot, &st) == 0 || errno == EOVERFLOW;
		free(nameslashdot);
		return dir;
	}
	return false;
}