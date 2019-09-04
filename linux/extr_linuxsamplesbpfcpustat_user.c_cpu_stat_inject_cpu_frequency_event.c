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

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_HIGHEST_FREQ ; 
 int /*<<< orphan*/  CPUFREQ_LOWEST_FREQ ; 
 int /*<<< orphan*/  CPUFREQ_MAX_SYSFS_PATH ; 
 int /*<<< orphan*/  O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int write (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpu_stat_inject_cpu_frequency_event(void)
{
	int len, fd;

	fd = open(CPUFREQ_MAX_SYSFS_PATH, O_WRONLY);
	if (fd < 0) {
		printf("failed to open scaling_max_freq, errno=%d\n", errno);
		return fd;
	}

	len = write(fd, CPUFREQ_LOWEST_FREQ, strlen(CPUFREQ_LOWEST_FREQ));
	if (len < 0) {
		printf("failed to open scaling_max_freq, errno=%d\n", errno);
		goto err;
	}

	len = write(fd, CPUFREQ_HIGHEST_FREQ, strlen(CPUFREQ_HIGHEST_FREQ));
	if (len < 0) {
		printf("failed to open scaling_max_freq, errno=%d\n", errno);
		goto err;
	}

err:
	close(fd);
	return len;
}