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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int find_freq_from_fid (int /*<<< orphan*/ ) ; 
 int find_millivolts_from_vid (int /*<<< orphan*/ ) ; 
 int get_fidvid (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int main (int argc, char *argv[])
{
	int err;
	int cpu;
	uint32_t fid, vid;

	if (argc < 2)
		cpu = 0;
	else
		cpu = strtoul(argv[1], NULL, 0);

	err = get_fidvid(cpu, &fid, &vid);

	if (err) {
		printf("can't get fid, vid from MSR\n");
		printf("Possible trouble: you don't run a powernow-k8 capable cpu\n");
		printf("or you are not root, or the msr driver is not present\n");
		exit(1);
	}

	
	printf("cpu %d currently at %d MHz and %d mV\n",
			cpu,
			find_freq_from_fid(fid),
			find_millivolts_from_vid(vid));
	
	return 0;
}