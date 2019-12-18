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
typedef  scalar_t__ u64 ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ar_loccookie; } ;
struct gfs2_sbd {TYPE_1__ sd_args; } ;
struct gfs2_leaf {scalar_t__ lf_entries; int /*<<< orphan*/  lf_next; scalar_t__ lf_depth; } ;
struct gfs2_inode {int dummy; } ;
struct gfs2_dirent {int dummy; } ;
struct dirent_gather {unsigned int offset; struct gfs2_dirent const** pdent; } ;
struct dir_context {int dummy; } ;
struct buffer_head {scalar_t__ b_blocknr; int /*<<< orphan*/  b_size; scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EIO ; 
 int ENOMEM ; 
 unsigned int GFS2_DIR_MAX_DEPTH ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 scalar_t__ IS_ERR (struct gfs2_dirent*) ; 
 int PTR_ERR (struct gfs2_dirent*) ; 
 unsigned int be16_to_cpu (scalar_t__) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int do_filldir_main (struct gfs2_inode*,struct dir_context*,struct gfs2_dirent**,unsigned int,unsigned int,int*) ; 
 int /*<<< orphan*/  fs_warn (struct gfs2_sbd*,char*,unsigned long long,unsigned int,unsigned int) ; 
 int get_leaf (struct gfs2_inode*,scalar_t__,struct buffer_head**) ; 
 struct buffer_head** gfs2_alloc_sort_buffer (unsigned int) ; 
 int /*<<< orphan*/  gfs2_consist_inode (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_dirent_gather ; 
 struct gfs2_dirent* gfs2_dirent_scan (struct inode*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dirent_gather*) ; 
 int gfs2_set_cookies (struct gfs2_sbd*,struct buffer_head*,unsigned int,struct gfs2_dirent**,unsigned int) ; 
 int /*<<< orphan*/  kvfree (struct buffer_head**) ; 

__attribute__((used)) static int gfs2_dir_read_leaf(struct inode *inode, struct dir_context *ctx,
			      int *copied, unsigned *depth,
			      u64 leaf_no)
{
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	struct buffer_head *bh;
	struct gfs2_leaf *lf;
	unsigned entries = 0, entries2 = 0;
	unsigned leaves = 0, leaf = 0, offset, sort_offset;
	struct gfs2_dirent **darr, *dent;
	struct dirent_gather g;
	struct buffer_head **larr;
	int error, i, need_sort = 0, sort_id;
	u64 lfn = leaf_no;

	do {
		error = get_leaf(ip, lfn, &bh);
		if (error)
			goto out;
		lf = (struct gfs2_leaf *)bh->b_data;
		if (leaves == 0)
			*depth = be16_to_cpu(lf->lf_depth);
		entries += be16_to_cpu(lf->lf_entries);
		leaves++;
		lfn = be64_to_cpu(lf->lf_next);
		brelse(bh);
	} while(lfn);

	if (*depth < GFS2_DIR_MAX_DEPTH || !sdp->sd_args.ar_loccookie) {
		need_sort = 1;
		sort_offset = 0;
	}

	if (!entries)
		return 0;

	error = -ENOMEM;
	/*
	 * The extra 99 entries are not normally used, but are a buffer
	 * zone in case the number of entries in the leaf is corrupt.
	 * 99 is the maximum number of entries that can fit in a single
	 * leaf block.
	 */
	larr = gfs2_alloc_sort_buffer((leaves + entries + 99) * sizeof(void *));
	if (!larr)
		goto out;
	darr = (struct gfs2_dirent **)(larr + leaves);
	g.pdent = (const struct gfs2_dirent **)darr;
	g.offset = 0;
	lfn = leaf_no;

	do {
		error = get_leaf(ip, lfn, &bh);
		if (error)
			goto out_free;
		lf = (struct gfs2_leaf *)bh->b_data;
		lfn = be64_to_cpu(lf->lf_next);
		if (lf->lf_entries) {
			offset = g.offset;
			entries2 += be16_to_cpu(lf->lf_entries);
			dent = gfs2_dirent_scan(inode, bh->b_data, bh->b_size,
						gfs2_dirent_gather, NULL, &g);
			error = PTR_ERR(dent);
			if (IS_ERR(dent))
				goto out_free;
			if (entries2 != g.offset) {
				fs_warn(sdp, "Number of entries corrupt in dir "
						"leaf %llu, entries2 (%u) != "
						"g.offset (%u)\n",
					(unsigned long long)bh->b_blocknr,
					entries2, g.offset);
				gfs2_consist_inode(ip);
				error = -EIO;
				goto out_free;
			}
			error = 0;
			sort_id = gfs2_set_cookies(sdp, bh, leaf, &darr[offset],
						   be16_to_cpu(lf->lf_entries));
			if (!need_sort && sort_id >= 0) {
				need_sort = 1;
				sort_offset = offset + sort_id;
			}
			larr[leaf++] = bh;
		} else {
			larr[leaf++] = NULL;
			brelse(bh);
		}
	} while(lfn);

	BUG_ON(entries2 != entries);
	error = do_filldir_main(ip, ctx, darr, entries, need_sort ?
				sort_offset : entries, copied);
out_free:
	for(i = 0; i < leaf; i++)
		brelse(larr[i]);
	kvfree(larr);
out:
	return error;
}