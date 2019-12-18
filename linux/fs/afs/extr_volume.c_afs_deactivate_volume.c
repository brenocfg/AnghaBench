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
struct afs_volume {int /*<<< orphan*/ * cache; int /*<<< orphan*/  flags; TYPE_1__* cell; int /*<<< orphan*/  proc_link; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  proc_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_VOLUME_DELETED ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  fscache_relinquish_cookie (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

void afs_deactivate_volume(struct afs_volume *volume)
{
	_enter("%s", volume->name);

	write_lock(&volume->cell->proc_lock);
	list_del_init(&volume->proc_link);
	write_unlock(&volume->cell->proc_lock);

#ifdef CONFIG_AFS_FSCACHE
	fscache_relinquish_cookie(volume->cache, NULL,
				  test_bit(AFS_VOLUME_DELETED, &volume->flags));
	volume->cache = NULL;
#endif

	_leave("");
}