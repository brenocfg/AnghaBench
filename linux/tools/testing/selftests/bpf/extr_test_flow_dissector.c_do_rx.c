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
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 char cfg_payload_char ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (int,scalar_t__,char*) ; 
 int recv (int,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_rx(int fd)
{
	char rbuf;
	int ret, num = 0;

	while (1) {
		ret = recv(fd, &rbuf, 1, MSG_DONTWAIT);
		if (ret == -1 && errno == EAGAIN)
			break;
		if (ret == -1)
			error(1, errno, "recv");
		if (rbuf != cfg_payload_char)
			error(1, 0, "recv: payload mismatch");
		num++;
	};

	return num;
}