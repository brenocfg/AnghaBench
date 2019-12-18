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
 scalar_t__ readn (int /*<<< orphan*/ ,void*,scalar_t__) ; 

__attribute__((used)) static int __do_read_fd(struct feat_fd *ff, void *addr, ssize_t size)
{
	ssize_t ret = readn(ff->fd, addr, size);

	if (ret != size)
		return ret < 0 ? (int)ret : -1;
	return 0;
}