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
struct afs_volume {TYPE_1__* cell; int /*<<< orphan*/  proc_link; int /*<<< orphan*/  vid; int /*<<< orphan*/  cache; } ;
struct TYPE_2__ {int /*<<< orphan*/  proc_lock; int /*<<< orphan*/  proc_volumes; int /*<<< orphan*/  cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  afs_volume_cache_index_def ; 
 int /*<<< orphan*/  fscache_acquire_cookie (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct afs_volume*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

void afs_activate_volume(struct afs_volume *volume)
{
#ifdef CONFIG_AFS_FSCACHE
	volume->cache = fscache_acquire_cookie(volume->cell->cache,
					       &afs_volume_cache_index_def,
					       &volume->vid, sizeof(volume->vid),
					       NULL, 0,
					       volume, 0, true);
#endif

	write_lock(&volume->cell->proc_lock);
	list_add_tail(&volume->proc_link, &volume->cell->proc_volumes);
	write_unlock(&volume->cell->proc_lock);
}