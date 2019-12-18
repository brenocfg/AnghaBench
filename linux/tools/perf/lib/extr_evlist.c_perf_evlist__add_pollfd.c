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
struct TYPE_4__ {TYPE_1__* priv; } ;
struct perf_evlist {TYPE_2__ pollfd; } ;
struct TYPE_3__ {void* ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 short POLLERR ; 
 short POLLHUP ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fdarray__add (TYPE_2__*,int,short) ; 

int perf_evlist__add_pollfd(struct perf_evlist *evlist, int fd,
			    void *ptr, short revent)
{
	int pos = fdarray__add(&evlist->pollfd, fd, revent | POLLERR | POLLHUP);

	if (pos >= 0) {
		evlist->pollfd.priv[pos].ptr = ptr;
		fcntl(fd, F_SETFL, O_NONBLOCK);
	}

	return pos;
}