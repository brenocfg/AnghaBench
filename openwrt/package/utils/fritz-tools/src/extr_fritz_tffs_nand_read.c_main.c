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
struct tffs_key_name_table {int size; int /*<<< orphan*/  entries; } ;
struct tffs_entry {int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  TFFS_ID_TABLE_NAME ; 
 int /*<<< orphan*/  basename (char*) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  find_entry (int /*<<< orphan*/ ,struct tffs_entry*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 char* mtddev ; 
 scalar_t__ mtdfd ; 
 scalar_t__ open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_key_names (struct tffs_entry*,struct tffs_key_name_table*) ; 
 int /*<<< orphan*/  parse_options (int,char**) ; 
 scalar_t__ print_all_key_names ; 
 int /*<<< orphan*/  progname ; 
 int /*<<< orphan*/  scan_mtd () ; 
 int /*<<< orphan*/  sectors ; 
 scalar_t__ show_all ; 
 int /*<<< orphan*/  show_all_key_names (struct tffs_key_name_table*) ; 
 int show_all_key_value_pairs (struct tffs_key_name_table*) ; 
 int show_matching_key_value (struct tffs_key_name_table*) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char *argv[])
{
	int ret = EXIT_FAILURE;
	struct tffs_entry name_table;
	struct tffs_key_name_table key_names;

	progname = basename(argv[0]);

	parse_options(argc, argv);

	mtdfd = open(mtddev, O_RDONLY);
	if (mtdfd < 0) {
		fprintf(stderr, "ERROR: Failed to open tffs device %s\n",
			mtddev);
		goto out;
	}

	if (!scan_mtd()) {
		fprintf(stderr, "ERROR: Parsing blocks from tffs device %s failed\n", mtddev);
		fprintf(stderr, "       Is byte-swapping (-b) required?\n");
		goto out_close;
	}

	if (!find_entry(TFFS_ID_TABLE_NAME, &name_table)) {
		fprintf(stderr, "ERROR: No name table found on tffs device %s\n",
			mtddev);
		goto out_free_sectors;
	}

	parse_key_names(&name_table, &key_names);
	if (key_names.size < 1) {
		fprintf(stderr, "ERROR: No name table found on tffs device %s\n",
			mtddev);
		goto out_free_entry;
	}

	if (print_all_key_names) {
		show_all_key_names(&key_names);
		ret = EXIT_SUCCESS;
	} else if (show_all) {
		ret = show_all_key_value_pairs(&key_names);
	} else {
		ret = show_matching_key_value(&key_names);
	}

	free(key_names.entries);
out_free_entry:
	free(name_table.val);
out_free_sectors:
	free(sectors);
out_close:
	close(mtdfd);
out:
	return ret;
}