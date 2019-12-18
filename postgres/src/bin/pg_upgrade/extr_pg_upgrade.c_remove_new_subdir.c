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
typedef  int /*<<< orphan*/  new_path ;
struct TYPE_2__ {char* pgdata; } ;

/* Variables and functions */
 int MAXPGPATH ; 
 int /*<<< orphan*/  check_ok () ; 
 TYPE_1__ new_cluster ; 
 int /*<<< orphan*/  pg_fatal (char*,char*) ; 
 int /*<<< orphan*/  prep_status (char*,char const*) ; 
 int /*<<< orphan*/  rmtree (char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*) ; 

__attribute__((used)) static void
remove_new_subdir(const char *subdir, bool rmtopdir)
{
	char		new_path[MAXPGPATH];

	prep_status("Deleting files from new %s", subdir);

	snprintf(new_path, sizeof(new_path), "%s/%s", new_cluster.pgdata, subdir);
	if (!rmtree(new_path, rmtopdir))
		pg_fatal("could not delete directory \"%s\"\n", new_path);

	check_ok();
}