#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct aa_loaddata {long revision; int /*<<< orphan*/ * dents; TYPE_1__* ns; } ;
struct TYPE_5__ {void* i_mtime; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 size_t AAFS_LOADDATA_DIR ; 
 size_t AAFS_LOADDATA_REVISION ; 
 int /*<<< orphan*/  AA_BUG (int) ; 
 void* current_time (TYPE_2__*) ; 
 TYPE_2__* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 

void __aa_loaddata_update(struct aa_loaddata *data, long revision)
{
	AA_BUG(!data);
	AA_BUG(!data->ns);
	AA_BUG(!data->dents[AAFS_LOADDATA_REVISION]);
	AA_BUG(!mutex_is_locked(&data->ns->lock));
	AA_BUG(data->revision > revision);

	data->revision = revision;
	d_inode(data->dents[AAFS_LOADDATA_DIR])->i_mtime =
		current_time(d_inode(data->dents[AAFS_LOADDATA_DIR]));
	d_inode(data->dents[AAFS_LOADDATA_REVISION])->i_mtime =
		current_time(d_inode(data->dents[AAFS_LOADDATA_REVISION]));
}