#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  basedir; scalar_t__ sync; } ;

/* Variables and functions */
 TYPE_1__* dir_data ; 
 scalar_t__ fsync_fname (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
dir_finish(void)
{
	if (dir_data->sync)
	{
		/*
		 * Files are fsynced when they are closed, but we need to fsync the
		 * directory entry here as well.
		 */
		if (fsync_fname(dir_data->basedir, true) != 0)
			return false;
	}
	return true;
}