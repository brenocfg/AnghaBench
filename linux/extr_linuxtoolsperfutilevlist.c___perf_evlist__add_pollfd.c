#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct perf_mmap {int dummy; } ;
struct TYPE_4__ {TYPE_1__* priv; } ;
struct perf_evlist {TYPE_2__ pollfd; } ;
struct TYPE_3__ {struct perf_mmap* ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 short POLLERR ; 
 short POLLHUP ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fdarray__add (TYPE_2__*,int,short) ; 

__attribute__((used)) static int __perf_evlist__add_pollfd(struct perf_evlist *evlist, int fd,
				     struct perf_mmap *map, short revent)
{
	int pos = fdarray__add(&evlist->pollfd, fd, revent | POLLERR | POLLHUP);
	/*
	 * Save the idx so that when we filter out fds POLLHUP'ed we can
	 * close the associated evlist->mmap[] entry.
	 */
	if (pos >= 0) {
		evlist->pollfd.priv[pos].ptr = map;

		fcntl(fd, F_SETFL, O_NONBLOCK);
	}

	return pos;
}