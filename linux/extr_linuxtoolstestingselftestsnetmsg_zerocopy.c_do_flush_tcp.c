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
 int MSG_DONTWAIT ; 
 int MSG_TRUNC ; 
 int bytes ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (int,scalar_t__,char*) ; 
 int /*<<< orphan*/  packets ; 
 int recv (int,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void do_flush_tcp(int fd)
{
	int ret;

	/* MSG_TRUNC flushes up to len bytes */
	ret = recv(fd, NULL, 1 << 21, MSG_TRUNC | MSG_DONTWAIT);
	if (ret == -1 && errno == EAGAIN)
		return;
	if (ret == -1)
		error(1, errno, "flush");
	if (!ret)
		return;

	packets++;
	bytes += ret;
}