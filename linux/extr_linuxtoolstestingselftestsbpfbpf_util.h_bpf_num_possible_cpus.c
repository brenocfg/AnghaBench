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
typedef  int /*<<< orphan*/  buff ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int sscanf (char*,char*,unsigned int*,unsigned int*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

__attribute__((used)) static inline unsigned int bpf_num_possible_cpus(void)
{
	static const char *fcpu = "/sys/devices/system/cpu/possible";
	unsigned int start, end, possible_cpus = 0;
	char buff[128];
	FILE *fp;
	int len, n, i, j = 0;

	fp = fopen(fcpu, "r");
	if (!fp) {
		printf("Failed to open %s: '%s'!\n", fcpu, strerror(errno));
		exit(1);
	}

	if (!fgets(buff, sizeof(buff), fp)) {
		printf("Failed to read %s!\n", fcpu);
		exit(1);
	}

	len = strlen(buff);
	for (i = 0; i <= len; i++) {
		if (buff[i] == ',' || buff[i] == '\0') {
			buff[i] = '\0';
			n = sscanf(&buff[j], "%u-%u", &start, &end);
			if (n <= 0) {
				printf("Failed to retrieve # possible CPUs!\n");
				exit(1);
			} else if (n == 1) {
				end = start;
			}
			possible_cpus += end - start + 1;
			j = i + 1;
		}
	}

	fclose(fp);

	return possible_cpus;
}