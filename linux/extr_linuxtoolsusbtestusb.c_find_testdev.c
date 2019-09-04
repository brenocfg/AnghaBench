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
struct testdev {char* name; int ifnum; struct testdev* next; int /*<<< orphan*/  speed; } ;
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int FTW_F ; 
 struct testdev* calloc (int,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,int) ; 
 int /*<<< orphan*/  free (struct testdev*) ; 
 int /*<<< orphan*/  perror (char const*) ; 
 char* speed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* strdup (char const*) ; 
 int testdev_ifnum (int /*<<< orphan*/ *) ; 
 struct testdev* testdevs ; 

__attribute__((used)) static int find_testdev(const char *name, const struct stat *sb, int flag)
{
	FILE				*fd;
	int				ifnum;
	struct testdev			*entry;

	(void)sb; /* unused */

	if (flag != FTW_F)
		return 0;

	fd = fopen(name, "rb");
	if (!fd) {
		perror(name);
		return 0;
	}

	ifnum = testdev_ifnum(fd);
	fclose(fd);
	if (ifnum < 0)
		return 0;

	entry = calloc(1, sizeof *entry);
	if (!entry)
		goto nomem;

	entry->name = strdup(name);
	if (!entry->name) {
		free(entry);
nomem:
		perror("malloc");
		return 0;
	}

	entry->ifnum = ifnum;

	/* FIXME update USBDEVFS_CONNECTINFO so it tells about high speed etc */

	fprintf(stderr, "%s speed\t%s\t%u\n",
		speed(entry->speed), entry->name, entry->ifnum);

	entry->next = testdevs;
	testdevs = entry;
	return 0;
}