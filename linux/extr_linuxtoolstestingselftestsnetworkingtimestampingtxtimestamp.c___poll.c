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
struct pollfd {int fd; } ;
typedef  int /*<<< orphan*/  pollfd ;

/* Variables and functions */
 int /*<<< orphan*/  cfg_poll_timeout ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (struct pollfd*,int /*<<< orphan*/ ,int) ; 
 int poll (struct pollfd*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __poll(int fd)
{
	struct pollfd pollfd;
	int ret;

	memset(&pollfd, 0, sizeof(pollfd));
	pollfd.fd = fd;
	ret = poll(&pollfd, 1, cfg_poll_timeout);
	if (ret != 1)
		error(1, errno, "poll");
}