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
struct TYPE_2__ {int num_blocks; size_t num_records; struct kvp_record* records; int /*<<< orphan*/  fname; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ENTRIES_PER_BLOCK ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fread (struct kvp_record*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvp_acquire_lock (int) ; 
 TYPE_1__* kvp_file_info ; 
 int /*<<< orphan*/  kvp_release_lock (int) ; 
 struct kvp_record* realloc (struct kvp_record*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void kvp_update_mem_state(int pool)
{
	FILE *filep;
	size_t records_read = 0;
	struct kvp_record *record = kvp_file_info[pool].records;
	struct kvp_record *readp;
	int num_blocks = kvp_file_info[pool].num_blocks;
	int alloc_unit = sizeof(struct kvp_record) * ENTRIES_PER_BLOCK;

	kvp_acquire_lock(pool);

	filep = fopen(kvp_file_info[pool].fname, "re");
	if (!filep) {
		syslog(LOG_ERR, "Failed to open file, pool: %d; error: %d %s", pool,
				errno, strerror(errno));
		kvp_release_lock(pool);
		exit(EXIT_FAILURE);
	}
	for (;;) {
		readp = &record[records_read];
		records_read += fread(readp, sizeof(struct kvp_record),
				ENTRIES_PER_BLOCK * num_blocks - records_read,
				filep);

		if (ferror(filep)) {
			syslog(LOG_ERR,
				"Failed to read file, pool: %d; error: %d %s",
				 pool, errno, strerror(errno));
			kvp_release_lock(pool);
			exit(EXIT_FAILURE);
		}

		if (!feof(filep)) {
			/*
			 * We have more data to read.
			 */
			num_blocks++;
			record = realloc(record, alloc_unit * num_blocks);

			if (record == NULL) {
				syslog(LOG_ERR, "malloc failed");
				kvp_release_lock(pool);
				exit(EXIT_FAILURE);
			}
			continue;
		}
		break;
	}

	kvp_file_info[pool].num_blocks = num_blocks;
	kvp_file_info[pool].records = record;
	kvp_file_info[pool].num_records = records_read;

	fclose(filep);
	kvp_release_lock(pool);
}