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
struct list_head {int dummy; } ;
struct compressed_bio {int compress_type; } ;
struct TYPE_2__ {int (* decompress_bio ) (struct list_head*,struct compressed_bio*) ;} ;

/* Variables and functions */
 TYPE_1__** btrfs_compress_op ; 
 struct list_head* get_workspace (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_workspace (int,struct list_head*) ; 
 int stub1 (struct list_head*,struct compressed_bio*) ; 

__attribute__((used)) static int btrfs_decompress_bio(struct compressed_bio *cb)
{
	struct list_head *workspace;
	int ret;
	int type = cb->compress_type;

	workspace = get_workspace(type, 0);
	ret = btrfs_compress_op[type]->decompress_bio(workspace, cb);
	put_workspace(type, workspace);

	return ret;
}