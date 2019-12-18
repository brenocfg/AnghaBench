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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int BPF_OBJ_MAP ; 
 int BPF_OBJ_PROG ; 
 int BPF_OBJ_UNKNOWN ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  p_err (char*,...) ; 
 int readlink (char*,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ strstr (char*,char*) ; 

int get_fd_type(int fd)
{
	char path[PATH_MAX];
	char buf[512];
	ssize_t n;

	snprintf(path, sizeof(path), "/proc/self/fd/%d", fd);

	n = readlink(path, buf, sizeof(buf));
	if (n < 0) {
		p_err("can't read link type: %s", strerror(errno));
		return -1;
	}
	if (n == sizeof(path)) {
		p_err("can't read link type: path too long!");
		return -1;
	}

	if (strstr(buf, "bpf-map"))
		return BPF_OBJ_MAP;
	else if (strstr(buf, "bpf-prog"))
		return BPF_OBJ_PROG;

	return BPF_OBJ_UNKNOWN;
}