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
 int /*<<< orphan*/  MSG_ZEROCOPY ; 
 int cfg_payload_len ; 
 scalar_t__ cfg_zerocopy ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int send (int,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_tcp(int fd, char *data)
{
	int ret, done = 0, count = 0;

	while (done < cfg_payload_len) {
		ret = send(fd, data + done, cfg_payload_len - done,
			   cfg_zerocopy ? MSG_ZEROCOPY : 0);
		if (ret == -1)
			error(1, errno, "write");

		done += ret;
		count++;
	}

	return count;
}