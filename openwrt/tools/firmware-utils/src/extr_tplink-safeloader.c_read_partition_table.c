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
struct flash_partition_entry {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  add_flash_partition (struct flash_partition_entry*,size_t,char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int fread (char*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 char* memchr (char*,int,int) ; 
 scalar_t__ memcmp (char*,char const*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 unsigned long strtoul (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int read_partition_table(
		FILE *file, long offset,
		struct flash_partition_entry *entries, size_t max_entries,
		int type)
{
	char buf[2048];
	char *ptr, *end;
	const char *parthdr = NULL;
	const char *fwuphdr = "fwup-ptn";
	const char *flashhdr = "partition";

	/* TODO: search for the partition table */

	switch(type) {
		case 0:
			parthdr = fwuphdr;
			break;
		case 1:
			parthdr = flashhdr;
			break;
		default:
			error(1, 0, "Invalid partition table");
	}

	if (fseek(file, offset, SEEK_SET) < 0)
		error(1, errno, "Can not seek in the firmware");

	if (fread(buf, 2048, 1, file) != 1)
		error(1, errno, "Can not read fwup-ptn from the firmware");

	buf[2047] = '\0';

	/* look for the partition header */
	if (memcmp(buf, parthdr, strlen(parthdr)) != 0) {
		fprintf(stderr, "DEBUG: can not find fwuphdr\n");
		return 1;
	}

	ptr = buf;
	end = buf + sizeof(buf);
	while ((ptr + strlen(parthdr)) < end &&
			memcmp(ptr, parthdr, strlen(parthdr)) == 0) {
		char *end_part;
		char *end_element;

		char name[32] = { 0 };
		int name_len = 0;
		unsigned long base = 0;
		unsigned long size = 0;

		end_part = memchr(ptr, '\n', (end - ptr));
		if (end_part == NULL) {
			/* in theory this should never happen, because a partition always ends with 0x09, 0x0D, 0x0A */
			break;
		}

		for (int i = 0; i <= 4; i++) {
			if (end_part <= ptr)
				break;

			end_element = memchr(ptr, 0x20, (end_part - ptr));
			if (end_element == NULL) {
				error(1, errno, "Ignoring the rest of the partition entries.");
				break;
			}

			switch (i) {
				/* partition header */
				case 0:
					ptr = end_element + 1;
					continue;
				/* name */
				case 1:
					name_len = (end_element - ptr) > 31 ? 31 : (end_element - ptr);
					strncpy(name, ptr, name_len);
					name[name_len] = '\0';
					ptr = end_element + 1;
					continue;

				/* string "base" */
				case 2:
					ptr = end_element + 1;
					continue;

				/* actual base */
				case 3:
					base = strtoul(ptr, NULL, 16);
					ptr = end_element + 1;
					continue;

				/* string "size" */
				case 4:
					ptr = end_element + 1;
					/* actual size. The last element doesn't have a sepeartor */
					size = strtoul(ptr, NULL, 16);
					/* the part ends with 0x09, 0x0d, 0x0a */
					ptr = end_part + 1;
					add_flash_partition(entries, max_entries, name, base, size);
					continue;
			}
		}
	}

	return 0;
}