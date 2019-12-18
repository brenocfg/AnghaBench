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
typedef  scalar_t__ u32 ;
struct gfs2_sbd {int dummy; } ;
struct gfs2_meta_header {int /*<<< orphan*/  mh_magic; } ;
struct buffer_head {scalar_t__ b_blocknr; scalar_t__ b_data; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ GFS2_MAGIC ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_err (struct gfs2_sbd*,char*,unsigned long long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int gfs2_meta_check(struct gfs2_sbd *sdp,
				    struct buffer_head *bh)
{
	struct gfs2_meta_header *mh = (struct gfs2_meta_header *)bh->b_data;
	u32 magic = be32_to_cpu(mh->mh_magic);
	if (unlikely(magic != GFS2_MAGIC)) {
		fs_err(sdp, "Magic number missing at %llu\n",
		       (unsigned long long)bh->b_blocknr);
		return -EIO;
	}
	return 0;
}