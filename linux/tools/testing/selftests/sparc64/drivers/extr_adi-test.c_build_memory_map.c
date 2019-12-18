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
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_PRINT_L1 (char*,...) ; 
 void** end_addr ; 
 int errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 size_t range_count ; 
 void** start_addr ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 
 char* strstr (char*,char*) ; 
 void* strtoull (char*,char**,int) ; 
 char* system_ram_str ; 

__attribute__((used)) static int build_memory_map(void)
{
	char line[256];
	FILE *fp;
	int i;

	range_count = 0;

	fp = fopen("/proc/iomem", "r");
	if (!fp) {
		fprintf(stderr, "/proc/iomem: error %d: %s\n",
			errno, strerror(errno));
		return -errno;
	}

	while (fgets(line, sizeof(line), fp) != 0) {
		if (strstr(line, system_ram_str)) {
			char *dash, *end_ptr;

			/* Given a line like this:
			 * d0400000-10ffaffff : System RAM
			 * replace the "-" with a space
			 */
			dash = strstr(line, "-");
			dash[0] = 0x20;

			start_addr[range_count] = strtoull(line, &end_ptr, 16);
			end_addr[range_count] = strtoull(end_ptr, NULL, 16);
			range_count++;
		}
	}

	fclose(fp);

	DEBUG_PRINT_L1("RAM Ranges\n");
	for (i = 0; i < range_count; i++)
		DEBUG_PRINT_L1("\trange %d: 0x%llx\t- 0x%llx\n",
			       i, start_addr[i], end_addr[i]);

	if (range_count == 0) {
		fprintf(stderr, "No valid address ranges found.  Error.\n");
		return -1;
	}

	return 0;
}