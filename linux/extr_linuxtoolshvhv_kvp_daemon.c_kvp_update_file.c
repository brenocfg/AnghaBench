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
struct kvp_record {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_records; int /*<<< orphan*/  records; int /*<<< orphan*/  fname; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvp_acquire_lock (int) ; 
 TYPE_1__* kvp_file_info ; 
 int /*<<< orphan*/  kvp_release_lock (int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static void kvp_update_file(int pool)
{
	FILE *filep;

	/*
	 * We are going to write our in-memory registry out to
	 * disk; acquire the lock first.
	 */
	kvp_acquire_lock(pool);

	filep = fopen(kvp_file_info[pool].fname, "we");
	if (!filep) {
		syslog(LOG_ERR, "Failed to open file, pool: %d; error: %d %s", pool,
				errno, strerror(errno));
		kvp_release_lock(pool);
		exit(EXIT_FAILURE);
	}

	fwrite(kvp_file_info[pool].records, sizeof(struct kvp_record),
				kvp_file_info[pool].num_records, filep);

	if (ferror(filep) || fclose(filep)) {
		kvp_release_lock(pool);
		syslog(LOG_ERR, "Failed to write file, pool: %d", pool);
		exit(EXIT_FAILURE);
	}

	kvp_release_lock(pool);
}