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
struct pollfd {int fd; int events; } ;

/* Variables and functions */
 int POLLERR ; 
 int POLLIN ; 
 int poll (struct pollfd*,int,int) ; 

int sync_wait(int fd, int timeout)
{
	struct pollfd fds;

	fds.fd = fd;
	fds.events = POLLIN | POLLERR;

	return poll(&fds, 1, timeout);
}