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
struct TYPE_3__ {int /*<<< orphan*/  bh; } ;
struct TYPE_4__ {int lstart; TYPE_1__ epos; } ;
struct udf_inode_info {TYPE_2__ cached_extent; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 struct udf_inode_info* UDF_I (struct inode*) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __udf_clear_extent_cache(struct inode *inode)
{
	struct udf_inode_info *iinfo = UDF_I(inode);

	if (iinfo->cached_extent.lstart != -1) {
		brelse(iinfo->cached_extent.epos.bh);
		iinfo->cached_extent.lstart = -1;
	}
}