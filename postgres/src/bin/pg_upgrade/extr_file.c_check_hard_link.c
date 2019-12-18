#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  new_link_file ;
typedef  int /*<<< orphan*/  existing_file ;
struct TYPE_4__ {char* pgdata; } ;
struct TYPE_3__ {char* pgdata; } ;

/* Variables and functions */
 int MAXPGPATH ; 
 int /*<<< orphan*/  errno ; 
 TYPE_2__ new_cluster ; 
 TYPE_1__ old_cluster ; 
 int /*<<< orphan*/  pg_fatal (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ pg_link_file (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (char*) ; 

void
check_hard_link(void)
{
	char		existing_file[MAXPGPATH];
	char		new_link_file[MAXPGPATH];

	snprintf(existing_file, sizeof(existing_file), "%s/PG_VERSION", old_cluster.pgdata);
	snprintf(new_link_file, sizeof(new_link_file), "%s/PG_VERSION.linktest", new_cluster.pgdata);
	unlink(new_link_file);		/* might fail */

	if (pg_link_file(existing_file, new_link_file) < 0)
		pg_fatal("could not create hard link between old and new data directories: %s\n"
				 "In link mode the old and new data directories must be on the same file system.\n",
				 strerror(errno));

	unlink(new_link_file);
}