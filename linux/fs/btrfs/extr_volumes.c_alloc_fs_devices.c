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
typedef  int /*<<< orphan*/  u8 ;
struct btrfs_fs_devices {int /*<<< orphan*/  metadata_uuid; int /*<<< orphan*/  fsid; int /*<<< orphan*/  fs_list; int /*<<< orphan*/  alloc_list; int /*<<< orphan*/  devices; int /*<<< orphan*/  device_list_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FSID_SIZE ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct btrfs_fs_devices* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct btrfs_fs_devices* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct btrfs_fs_devices *alloc_fs_devices(const u8 *fsid,
						 const u8 *metadata_fsid)
{
	struct btrfs_fs_devices *fs_devs;

	fs_devs = kzalloc(sizeof(*fs_devs), GFP_KERNEL);
	if (!fs_devs)
		return ERR_PTR(-ENOMEM);

	mutex_init(&fs_devs->device_list_mutex);

	INIT_LIST_HEAD(&fs_devs->devices);
	INIT_LIST_HEAD(&fs_devs->alloc_list);
	INIT_LIST_HEAD(&fs_devs->fs_list);
	if (fsid)
		memcpy(fs_devs->fsid, fsid, BTRFS_FSID_SIZE);

	if (metadata_fsid)
		memcpy(fs_devs->metadata_uuid, metadata_fsid, BTRFS_FSID_SIZE);
	else if (fsid)
		memcpy(fs_devs->metadata_uuid, fsid, BTRFS_FSID_SIZE);

	return fs_devs;
}