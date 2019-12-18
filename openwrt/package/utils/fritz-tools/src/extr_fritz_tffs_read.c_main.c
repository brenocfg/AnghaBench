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
typedef  int /*<<< orphan*/  uint8_t ;
struct tffs_key_name_table {int size; int /*<<< orphan*/ * entries; } ;
struct tffs_entry {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  TFFS_ID_TABLE_NAME ; 
 int /*<<< orphan*/  basename (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct tffs_entry*) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ fread (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 scalar_t__ ftell (int /*<<< orphan*/ *) ; 
 char* input_file ; 
 int /*<<< orphan*/ * malloc (scalar_t__) ; 
 int /*<<< orphan*/  parse_key_names (struct tffs_entry*,struct tffs_key_name_table*) ; 
 int /*<<< orphan*/  parse_options (int,char**) ; 
 scalar_t__ print_all_key_names ; 
 int /*<<< orphan*/  progname ; 
 scalar_t__ show_all ; 
 int /*<<< orphan*/  show_all_key_names (struct tffs_key_name_table*) ; 
 int show_all_key_value_pairs (int /*<<< orphan*/ *,struct tffs_key_name_table*) ; 
 int show_matching_key_value (int /*<<< orphan*/ *,struct tffs_key_name_table*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ tffs_size ; 

int main(int argc, char *argv[])
{
	int ret = EXIT_FAILURE;
	uint8_t *buffer;
	FILE *fp;
	struct tffs_entry name_table;
	struct tffs_key_name_table key_names;

	progname = basename(argv[0]);

	parse_options(argc, argv);

	fp = fopen(input_file, "r");

	if (!fp) {
		fprintf(stderr, "ERROR: Failed to open tffs input file %s\n",
			input_file);
		goto out;
	}

	if (tffs_size == 0) {
		fseek(fp, 0L, SEEK_END);
		tffs_size = ftell(fp);
		fseek(fp, 0L, SEEK_SET);
	}

	buffer = malloc(tffs_size);

	if (fread(buffer, 1, tffs_size, fp) != tffs_size) {
		fprintf(stderr, "ERROR: Failed read tffs file %s\n",
			input_file);
		goto out_free;
	}

	if (!find_entry(buffer, TFFS_ID_TABLE_NAME, &name_table)) {
		fprintf(stderr,"ERROR: No name table found in tffs file %s\n",
			input_file);
		fprintf(stderr,"       Is byte-swapping (-b) required?\n");
		goto out_free;
	}

	parse_key_names(&name_table, &key_names);
	if (key_names.size < 1) {
		fprintf(stderr, "ERROR: No name table found in tffs file %s\n",
			input_file);
		goto out_free_names;
	}

	if (print_all_key_names) {
		show_all_key_names(&key_names);
		ret = EXIT_SUCCESS;
	} else if (show_all) {
		ret = show_all_key_value_pairs(buffer, &key_names);
	} else {
		ret = show_matching_key_value(buffer, &key_names);
	}

out_free_names:
	free(key_names.entries);
out_free:
	fclose(fp);
	free(buffer);
out:
	return ret;
}