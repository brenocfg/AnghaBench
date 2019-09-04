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
struct btrfs_path {int dummy; } ;
struct btrfs_disk_key {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  key; } ;

/* Variables and functions */
 TYPE_1__* path_current_item (struct btrfs_path*) ; 

__attribute__((used)) static inline const struct btrfs_disk_key *path_current_disk_key(struct btrfs_path *path)
{
    return (const struct btrfs_disk_key *) &path_current_item(path)->key;
}