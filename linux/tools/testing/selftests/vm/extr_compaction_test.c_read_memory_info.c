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
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 unsigned long atoll (char*) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/ * popen (char*,char*) ; 

int read_memory_info(unsigned long *memfree, unsigned long *hugepagesize)
{
	char  buffer[256] = {0};
	char *cmd = "cat /proc/meminfo | grep -i memfree | grep -o '[0-9]*'";
	FILE *cmdfile = popen(cmd, "r");

	if (!(fgets(buffer, sizeof(buffer), cmdfile))) {
		perror("Failed to read meminfo\n");
		return -1;
	}

	pclose(cmdfile);

	*memfree = atoll(buffer);
	cmd = "cat /proc/meminfo | grep -i hugepagesize | grep -o '[0-9]*'";
	cmdfile = popen(cmd, "r");

	if (!(fgets(buffer, sizeof(buffer), cmdfile))) {
		perror("Failed to read meminfo\n");
		return -1;
	}

	pclose(cmdfile);
	*hugepagesize = atoll(buffer);

	return 0;
}