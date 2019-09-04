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
struct TYPE_2__ {int lstart; int /*<<< orphan*/  epos; } ;
struct udf_inode_info {int /*<<< orphan*/  i_extent_cache_lock; TYPE_1__ cached_extent; } ;
struct inode {int dummy; } ;
struct extent_position {scalar_t__ bh; } ;
typedef  int loff_t ;

/* Variables and functions */
 struct udf_inode_info* UDF_I (struct inode*) ; 
 int /*<<< orphan*/  get_bh (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (struct extent_position*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int udf_read_extent_cache(struct inode *inode, loff_t bcount,
				 loff_t *lbcount, struct extent_position *pos)
{
	struct udf_inode_info *iinfo = UDF_I(inode);
	int ret = 0;

	spin_lock(&iinfo->i_extent_cache_lock);
	if ((iinfo->cached_extent.lstart <= bcount) &&
	    (iinfo->cached_extent.lstart != -1)) {
		/* Cache hit */
		*lbcount = iinfo->cached_extent.lstart;
		memcpy(pos, &iinfo->cached_extent.epos,
		       sizeof(struct extent_position));
		if (pos->bh)
			get_bh(pos->bh);
		ret = 1;
	}
	spin_unlock(&iinfo->i_extent_cache_lock);
	return ret;
}