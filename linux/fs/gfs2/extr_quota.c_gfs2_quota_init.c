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
typedef  unsigned int u64 ;
typedef  int u32 ;
struct kqid {int dummy; } ;
struct TYPE_2__ {unsigned int sb_bsize_shift; } ;
struct gfs2_sbd {unsigned int sd_quota_slots; unsigned int sd_qc_per_block; int /*<<< orphan*/  sd_quota_count; int /*<<< orphan*/  sd_quota_list; int /*<<< orphan*/ * sd_quota_bitmap; int /*<<< orphan*/  sd_qc_inode; TYPE_1__ sd_sb; } ;
struct gfs2_quota_data {unsigned int qd_slot; int qd_slot_count; int /*<<< orphan*/  qd_hlist; int /*<<< orphan*/  qd_list; scalar_t__ qd_change; int /*<<< orphan*/  qd_flags; } ;
struct gfs2_quota_change {int /*<<< orphan*/  qc_id; int /*<<< orphan*/  qc_flags; int /*<<< orphan*/  qc_change; } ;
struct gfs2_meta_header {int dummy; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gl; int /*<<< orphan*/  i_inode; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  scalar_t__ s64 ;
typedef  enum quota_type { ____Placeholder_quota_type } quota_type ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 unsigned int DIV_ROUND_UP (unsigned int,int) ; 
 int EIO ; 
 int ENOMEM ; 
 int GFP_NOFS ; 
 struct gfs2_inode* GFS2_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFS2_METATYPE_QC ; 
 int GFS2_QCF_USER ; 
 int GRPQUOTA ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 int /*<<< orphan*/  QDF_CHANGE ; 
 int USRQUOTA ; 
 int __GFP_NOWARN ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/ * __vmalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  fs_info (struct gfs2_sbd*,char*,unsigned int) ; 
 scalar_t__ gfs2_check_internal_file_size (int /*<<< orphan*/ ,int,int) ; 
 int gfs2_extent_map (int /*<<< orphan*/ *,unsigned int,int*,unsigned int*,int*) ; 
 struct buffer_head* gfs2_meta_ra (int /*<<< orphan*/ ,unsigned int,int) ; 
 scalar_t__ gfs2_metatype_check (struct gfs2_sbd*,struct buffer_head*,int /*<<< orphan*/ ) ; 
 unsigned int gfs2_qd_hash (struct gfs2_sbd*,struct kqid) ; 
 int /*<<< orphan*/  gfs2_quota_cleanup (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  hlist_bl_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int i_size_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/ * kzalloc (unsigned int,int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct kqid make_kqid (int /*<<< orphan*/ *,int,int) ; 
 struct gfs2_quota_data* qd_alloc (unsigned int,struct gfs2_sbd*,struct kqid) ; 
 int /*<<< orphan*/ * qd_hash_table ; 
 int /*<<< orphan*/  qd_lock ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bucket (unsigned int) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bucket (unsigned int) ; 
 int /*<<< orphan*/  test_and_set_bit (unsigned int,int /*<<< orphan*/ *) ; 

int gfs2_quota_init(struct gfs2_sbd *sdp)
{
	struct gfs2_inode *ip = GFS2_I(sdp->sd_qc_inode);
	u64 size = i_size_read(sdp->sd_qc_inode);
	unsigned int blocks = size >> sdp->sd_sb.sb_bsize_shift;
	unsigned int x, slot = 0;
	unsigned int found = 0;
	unsigned int hash;
	unsigned int bm_size;
	u64 dblock;
	u32 extlen = 0;
	int error;

	if (gfs2_check_internal_file_size(sdp->sd_qc_inode, 1, 64 << 20))
		return -EIO;

	sdp->sd_quota_slots = blocks * sdp->sd_qc_per_block;
	bm_size = DIV_ROUND_UP(sdp->sd_quota_slots, 8 * sizeof(unsigned long));
	bm_size *= sizeof(unsigned long);
	error = -ENOMEM;
	sdp->sd_quota_bitmap = kzalloc(bm_size, GFP_NOFS | __GFP_NOWARN);
	if (sdp->sd_quota_bitmap == NULL)
		sdp->sd_quota_bitmap = __vmalloc(bm_size, GFP_NOFS |
						 __GFP_ZERO, PAGE_KERNEL);
	if (!sdp->sd_quota_bitmap)
		return error;

	for (x = 0; x < blocks; x++) {
		struct buffer_head *bh;
		const struct gfs2_quota_change *qc;
		unsigned int y;

		if (!extlen) {
			int new = 0;
			error = gfs2_extent_map(&ip->i_inode, x, &new, &dblock, &extlen);
			if (error)
				goto fail;
		}
		error = -EIO;
		bh = gfs2_meta_ra(ip->i_gl, dblock, extlen);
		if (!bh)
			goto fail;
		if (gfs2_metatype_check(sdp, bh, GFS2_METATYPE_QC)) {
			brelse(bh);
			goto fail;
		}

		qc = (const struct gfs2_quota_change *)(bh->b_data + sizeof(struct gfs2_meta_header));
		for (y = 0; y < sdp->sd_qc_per_block && slot < sdp->sd_quota_slots;
		     y++, slot++) {
			struct gfs2_quota_data *qd;
			s64 qc_change = be64_to_cpu(qc->qc_change);
			u32 qc_flags = be32_to_cpu(qc->qc_flags);
			enum quota_type qtype = (qc_flags & GFS2_QCF_USER) ?
						USRQUOTA : GRPQUOTA;
			struct kqid qc_id = make_kqid(&init_user_ns, qtype,
						      be32_to_cpu(qc->qc_id));
			qc++;
			if (!qc_change)
				continue;

			hash = gfs2_qd_hash(sdp, qc_id);
			qd = qd_alloc(hash, sdp, qc_id);
			if (qd == NULL) {
				brelse(bh);
				goto fail;
			}

			set_bit(QDF_CHANGE, &qd->qd_flags);
			qd->qd_change = qc_change;
			qd->qd_slot = slot;
			qd->qd_slot_count = 1;

			spin_lock(&qd_lock);
			BUG_ON(test_and_set_bit(slot, sdp->sd_quota_bitmap));
			list_add(&qd->qd_list, &sdp->sd_quota_list);
			atomic_inc(&sdp->sd_quota_count);
			spin_unlock(&qd_lock);

			spin_lock_bucket(hash);
			hlist_bl_add_head_rcu(&qd->qd_hlist, &qd_hash_table[hash]);
			spin_unlock_bucket(hash);

			found++;
		}

		brelse(bh);
		dblock++;
		extlen--;
	}

	if (found)
		fs_info(sdp, "found %u quota changes\n", found);

	return 0;

fail:
	gfs2_quota_cleanup(sdp);
	return error;
}