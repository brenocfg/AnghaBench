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
struct feat_fd {int /*<<< orphan*/  fd; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ writen (int /*<<< orphan*/ ,void const*,size_t) ; 

__attribute__((used)) static int __do_write_fd(struct feat_fd *ff, const void *buf, size_t size)
{
	ssize_t ret = writen(ff->fd, buf, size);

	if (ret != (ssize_t)size)
		return ret < 0 ? (int)ret : -1;
	return 0;
}