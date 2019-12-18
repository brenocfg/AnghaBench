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
 scalar_t__ close (int) ; 
 int dstfd ; 
 int /*<<< orphan*/  dstpath ; 
 int /*<<< orphan*/  pg_fatal (char*,int /*<<< orphan*/ ) ; 

void
close_target_file(void)
{
	if (dstfd == -1)
		return;

	if (close(dstfd) != 0)
		pg_fatal("could not close target file \"%s\": %m",
				 dstpath);

	dstfd = -1;
}