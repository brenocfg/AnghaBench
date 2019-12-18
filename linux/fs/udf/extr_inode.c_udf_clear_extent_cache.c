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
struct udf_inode_info {int /*<<< orphan*/  i_extent_cache_lock; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 struct udf_inode_info* UDF_I (struct inode*) ; 
 int /*<<< orphan*/  __udf_clear_extent_cache (struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void udf_clear_extent_cache(struct inode *inode)
{
	struct udf_inode_info *iinfo = UDF_I(inode);

	spin_lock(&iinfo->i_extent_cache_lock);
	__udf_clear_extent_cache(inode);
	spin_unlock(&iinfo->i_extent_cache_lock);
}