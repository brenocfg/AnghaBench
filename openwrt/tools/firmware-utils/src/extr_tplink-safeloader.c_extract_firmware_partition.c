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
struct flash_partition_entry {char* name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char*) ; 
 int /*<<< orphan*/  write_partition (int /*<<< orphan*/ *,size_t,struct flash_partition_entry*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int extract_firmware_partition(FILE *input_file, size_t firmware_offset, struct flash_partition_entry *entry, const char *output_directory)
{
	FILE *output_file;
	char output[PATH_MAX];

	snprintf(output, PATH_MAX, "%s/%s", output_directory, entry->name);
	output_file = fopen(output, "wb+");
	if (output_file == NULL) {
		error(1, errno, "Can not open output file %s", output);
	}

	write_partition(input_file, firmware_offset, entry, output_file);

	fclose(output_file);

	return 0;
}