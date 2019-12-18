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
struct orangefs_object_kref {int /*<<< orphan*/  khandle; int /*<<< orphan*/  fs_id; } ;
struct inode {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  khandle; int /*<<< orphan*/  fs_id; } ;
struct TYPE_4__ {scalar_t__ bitlock; scalar_t__ mapping_time; int /*<<< orphan*/  xattr_cache; scalar_t__ attr_valid; TYPE_1__ refn; } ;

/* Variables and functions */
 TYPE_2__* ORANGEFS_I (struct inode*) ; 
 int /*<<< orphan*/  hash_init (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 

__attribute__((used)) static int orangefs_set_inode(struct inode *inode, void *data)
{
	struct orangefs_object_kref *ref = (struct orangefs_object_kref *) data;
	ORANGEFS_I(inode)->refn.fs_id = ref->fs_id;
	ORANGEFS_I(inode)->refn.khandle = ref->khandle;
	ORANGEFS_I(inode)->attr_valid = 0;
	hash_init(ORANGEFS_I(inode)->xattr_cache);
	ORANGEFS_I(inode)->mapping_time = jiffies - 1;
	ORANGEFS_I(inode)->bitlock = 0;
	return 0;
}