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
struct erase_info_user {int /*<<< orphan*/  length; scalar_t__ start; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEMUNLOCK ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ioctl (int,int /*<<< orphan*/ ,struct erase_info_user*) ; 
 int mtd_check_open (char const*) ; 
 int /*<<< orphan*/  mtdsize ; 
 int quiet ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char const*,char) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static int
mtd_unlock(const char *mtd)
{
	struct erase_info_user mtdLockInfo;
	char *next = NULL;
	char *str = NULL;
	int fd;

	if (strchr(mtd, ':')) {
		str = strdup(mtd);
		mtd = str;
	}

	do {
		next = strchr(mtd, ':');
		if (next) {
			*next = 0;
			next++;
		}

		fd = mtd_check_open(mtd);
		if(fd < 0) {
			fprintf(stderr, "Could not open mtd device: %s\n", mtd);
			exit(1);
		}

		if (quiet < 2)
			fprintf(stderr, "Unlocking %s ...\n", mtd);

		mtdLockInfo.start = 0;
		mtdLockInfo.length = mtdsize;
		ioctl(fd, MEMUNLOCK, &mtdLockInfo);
		close(fd);
		mtd = next;
	} while (next);

	if (str)
		free(str);

	return 0;
}