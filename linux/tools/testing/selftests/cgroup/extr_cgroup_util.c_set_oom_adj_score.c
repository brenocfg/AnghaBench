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
 int O_APPEND ; 
 int O_WRONLY ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  close (int) ; 
 int dprintf (int,char*,int) ; 
 int open (char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

int set_oom_adj_score(int pid, int score)
{
	char path[PATH_MAX];
	int fd, len;

	sprintf(path, "/proc/%d/oom_score_adj", pid);

	fd = open(path, O_WRONLY | O_APPEND);
	if (fd < 0)
		return fd;

	len = dprintf(fd, "%d", score);
	if (len < 0) {
		close(fd);
		return len;
	}

	close(fd);
	return 0;
}