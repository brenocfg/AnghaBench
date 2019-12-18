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
typedef  int /*<<< orphan*/ * Walfile ;
struct TYPE_4__ {scalar_t__ compression; int /*<<< orphan*/  sync; } ;
struct TYPE_3__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  gzfp; } ;
typedef  TYPE_1__ DirectoryMethodFile ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_OK ; 
 int /*<<< orphan*/  Z_SYNC_FLUSH ; 
 TYPE_2__* dir_data ; 
 int fsync (int /*<<< orphan*/ ) ; 
 scalar_t__ gzflush (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dir_sync(Walfile f)
{
	Assert(f != NULL);

	if (!dir_data->sync)
		return 0;

#ifdef HAVE_LIBZ
	if (dir_data->compression > 0)
	{
		if (gzflush(((DirectoryMethodFile *) f)->gzfp, Z_SYNC_FLUSH) != Z_OK)
			return -1;
	}
#endif

	return fsync(((DirectoryMethodFile *) f)->fd);
}