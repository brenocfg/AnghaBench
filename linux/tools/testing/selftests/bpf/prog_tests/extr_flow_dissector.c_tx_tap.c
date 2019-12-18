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
struct iovec {size_t iov_len; void* iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct iovec*) ; 
 int writev (int,struct iovec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tx_tap(int fd, void *pkt, size_t len)
{
	struct iovec iov[] = {
		{
			.iov_len = len,
			.iov_base = pkt,
		},
	};
	return writev(fd, iov, ARRAY_SIZE(iov));
}