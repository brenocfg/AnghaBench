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
 int accept (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int do_accept(int fd)
{
	int fda = fd;

	fd = accept(fda, NULL, NULL);
	if (fd == -1)
		error(1, errno, "accept");
	if (close(fda))
		error(1, errno, "close listen sock");

	return fd;
}