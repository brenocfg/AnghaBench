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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 char* PROC_FASTOPEN_KEY ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  SOL_TCP ; 
 int /*<<< orphan*/  TCP_FASTOPEN_KEY ; 
 scalar_t__ do_rotate ; 
 scalar_t__ do_sockopt ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  key_len ; 
 int /*<<< orphan*/  lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_fd ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int,int,...) ; 
 scalar_t__ write (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void set_keys(int fd, uint32_t *keys)
{
	char buf[128];

	if (do_sockopt) {
		if (setsockopt(fd, SOL_TCP, TCP_FASTOPEN_KEY, keys,
		    key_len))
			error(1, errno, "Unable to set key");
		return;
	}
	if (do_rotate)
		snprintf(buf, 128, "%08x-%08x-%08x-%08x,%08x-%08x-%08x-%08x",
			 keys[0], keys[1], keys[2], keys[3], keys[4], keys[5],
			 keys[6], keys[7]);
	else
		snprintf(buf, 128, "%08x-%08x-%08x-%08x",
			 keys[0], keys[1], keys[2], keys[3]);
	lseek(proc_fd, 0, SEEK_SET);
	if (write(proc_fd, buf, sizeof(buf)) <= 0)
		error(1, errno, "Unable to write %s", PROC_FASTOPEN_KEY);
}