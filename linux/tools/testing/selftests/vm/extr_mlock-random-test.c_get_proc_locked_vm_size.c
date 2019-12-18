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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 
 int sscanf (char*,char*,unsigned long*) ; 
 scalar_t__ strstr (char*,char*) ; 

int get_proc_locked_vm_size(void)
{
	FILE *f;
	int ret = -1;
	char line[1024] = {0};
	unsigned long lock_size = 0;

	f = fopen("/proc/self/status", "r");
	if (!f) {
		perror("fopen");
		return -1;
	}

	while (fgets(line, 1024, f)) {
		if (strstr(line, "VmLck")) {
			ret = sscanf(line, "VmLck:\t%8lu kB", &lock_size);
			if (ret <= 0) {
				printf("sscanf() on VmLck error: %s: %d\n",
						line, ret);
				fclose(f);
				return -1;
			}
			fclose(f);
			return (int)(lock_size << 10);
		}
	}

	perror("cann't parse VmLck in /proc/self/status\n");
	fclose(f);
	return -1;
}