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
struct vm_boundaries {unsigned long start; unsigned long end; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  memset (struct vm_boundaries*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sscanf (char*,char*,unsigned long*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static int get_vm_area(unsigned long addr, struct vm_boundaries *area)
{
	FILE *file;
	int ret = 1;
	char line[1024] = {0};
	char *end_addr;
	char *stop;
	unsigned long start;
	unsigned long end;

	if (!area)
		return ret;

	file = fopen("/proc/self/maps", "r");
	if (!file) {
		perror("fopen");
		return ret;
	}

	memset(area, 0, sizeof(struct vm_boundaries));

	while(fgets(line, 1024, file)) {
		end_addr = strchr(line, '-');
		if (!end_addr) {
			printf("cannot parse /proc/self/maps\n");
			goto out;
		}
		*end_addr = '\0';
		end_addr++;
		stop = strchr(end_addr, ' ');
		if (!stop) {
			printf("cannot parse /proc/self/maps\n");
			goto out;
		}
		stop = '\0';

		sscanf(line, "%lx", &start);
		sscanf(end_addr, "%lx", &end);

		if (start <= addr && end > addr) {
			area->start = start;
			area->end = end;
			ret = 0;
			goto out;
		}
	}
out:
	fclose(file);
	return ret;
}