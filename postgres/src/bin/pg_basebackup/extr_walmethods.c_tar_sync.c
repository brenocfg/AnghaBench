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
typedef  int /*<<< orphan*/ * Walfile ;
struct TYPE_2__ {int /*<<< orphan*/  fd; scalar_t__ compression; int /*<<< orphan*/  sync; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int fsync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tar_clear_error () ; 
 TYPE_1__* tar_data ; 

__attribute__((used)) static int
tar_sync(Walfile f)
{
	Assert(f != NULL);
	tar_clear_error();

	if (!tar_data->sync)
		return 0;

	/*
	 * Always sync the whole tarfile, because that's all we can do. This makes
	 * no sense on compressed files, so just ignore those.
	 */
	if (tar_data->compression)
		return 0;

	return fsync(tar_data->fd);
}