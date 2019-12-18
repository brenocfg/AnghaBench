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
struct TYPE_4__ {int offset; } ;
struct TYPE_3__ {TYPE_2__ epos; int /*<<< orphan*/  lstart; } ;
struct udf_inode_info {int i_alloc_type; int /*<<< orphan*/  i_extent_cache_lock; TYPE_1__ cached_extent; } ;
struct short_ad {int dummy; } ;
struct long_ad {int dummy; } ;
struct inode {int dummy; } ;
struct extent_position {scalar_t__ bh; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
#define  ICBTAG_FLAG_AD_LONG 129 
#define  ICBTAG_FLAG_AD_SHORT 128 
 struct udf_inode_info* UDF_I (struct inode*) ; 
 int /*<<< orphan*/  __udf_clear_extent_cache (struct inode*) ; 
 int /*<<< orphan*/  get_bh (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,struct extent_position*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void udf_update_extent_cache(struct inode *inode, loff_t estart,
				    struct extent_position *pos)
{
	struct udf_inode_info *iinfo = UDF_I(inode);

	spin_lock(&iinfo->i_extent_cache_lock);
	/* Invalidate previously cached extent */
	__udf_clear_extent_cache(inode);
	if (pos->bh)
		get_bh(pos->bh);
	memcpy(&iinfo->cached_extent.epos, pos, sizeof(*pos));
	iinfo->cached_extent.lstart = estart;
	switch (iinfo->i_alloc_type) {
	case ICBTAG_FLAG_AD_SHORT:
		iinfo->cached_extent.epos.offset -= sizeof(struct short_ad);
		break;
	case ICBTAG_FLAG_AD_LONG:
		iinfo->cached_extent.epos.offset -= sizeof(struct long_ad);
		break;
	}
	spin_unlock(&iinfo->i_extent_cache_lock);
}