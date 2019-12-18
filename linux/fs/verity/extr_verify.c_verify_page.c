#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct page {int /*<<< orphan*/  index; } ;
struct merkle_tree_params {unsigned int digest_size; int num_levels; TYPE_3__* hash_alg; } ;
struct inode {TYPE_2__* i_sb; } ;
struct fsverity_info {int /*<<< orphan*/ * root_hash; struct merkle_tree_params tree_params; } ;
struct ahash_request {int dummy; } ;
typedef  int /*<<< orphan*/  pgoff_t ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {TYPE_1__* s_vop; } ;
struct TYPE_4__ {struct page* (* read_merkle_tree_page ) (struct inode*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int FS_VERITY_MAX_DIGEST_SIZE ; 
 int FS_VERITY_MAX_LEVELS ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int PTR_ERR (struct page*) ; 
 scalar_t__ PageChecked (struct page*) ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 scalar_t__ PageUptodate (struct page*) ; 
 int /*<<< orphan*/  SetPageChecked (struct page*) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int cmp_hashes (struct fsverity_info const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  extract_hash (struct page*,unsigned int,unsigned int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsverity_err (struct inode*,char*,int,int /*<<< orphan*/ ) ; 
 int fsverity_hash_page (struct merkle_tree_params const*,struct inode*,struct ahash_request*,struct page*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_at_level (struct merkle_tree_params const*,int /*<<< orphan*/  const,int,int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  pr_debug (char*,int,unsigned int const,unsigned int const,...) ; 
 int /*<<< orphan*/  pr_debug_ratelimited (char*,...) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 struct page* stub1 (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool verify_page(struct inode *inode, const struct fsverity_info *vi,
			struct ahash_request *req, struct page *data_page)
{
	const struct merkle_tree_params *params = &vi->tree_params;
	const unsigned int hsize = params->digest_size;
	const pgoff_t index = data_page->index;
	int level;
	u8 _want_hash[FS_VERITY_MAX_DIGEST_SIZE];
	const u8 *want_hash;
	u8 real_hash[FS_VERITY_MAX_DIGEST_SIZE];
	struct page *hpages[FS_VERITY_MAX_LEVELS];
	unsigned int hoffsets[FS_VERITY_MAX_LEVELS];
	int err;

	if (WARN_ON_ONCE(!PageLocked(data_page) || PageUptodate(data_page)))
		return false;

	pr_debug_ratelimited("Verifying data page %lu...\n", index);

	/*
	 * Starting at the leaf level, ascend the tree saving hash pages along
	 * the way until we find a verified hash page, indicated by PageChecked;
	 * or until we reach the root.
	 */
	for (level = 0; level < params->num_levels; level++) {
		pgoff_t hindex;
		unsigned int hoffset;
		struct page *hpage;

		hash_at_level(params, index, level, &hindex, &hoffset);

		pr_debug_ratelimited("Level %d: hindex=%lu, hoffset=%u\n",
				     level, hindex, hoffset);

		hpage = inode->i_sb->s_vop->read_merkle_tree_page(inode,
								  hindex);
		if (IS_ERR(hpage)) {
			err = PTR_ERR(hpage);
			fsverity_err(inode,
				     "Error %d reading Merkle tree page %lu",
				     err, hindex);
			goto out;
		}

		if (PageChecked(hpage)) {
			extract_hash(hpage, hoffset, hsize, _want_hash);
			want_hash = _want_hash;
			put_page(hpage);
			pr_debug_ratelimited("Hash page already checked, want %s:%*phN\n",
					     params->hash_alg->name,
					     hsize, want_hash);
			goto descend;
		}
		pr_debug_ratelimited("Hash page not yet checked\n");
		hpages[level] = hpage;
		hoffsets[level] = hoffset;
	}

	want_hash = vi->root_hash;
	pr_debug("Want root hash: %s:%*phN\n",
		 params->hash_alg->name, hsize, want_hash);
descend:
	/* Descend the tree verifying hash pages */
	for (; level > 0; level--) {
		struct page *hpage = hpages[level - 1];
		unsigned int hoffset = hoffsets[level - 1];

		err = fsverity_hash_page(params, inode, req, hpage, real_hash);
		if (err)
			goto out;
		err = cmp_hashes(vi, want_hash, real_hash, index, level - 1);
		if (err)
			goto out;
		SetPageChecked(hpage);
		extract_hash(hpage, hoffset, hsize, _want_hash);
		want_hash = _want_hash;
		put_page(hpage);
		pr_debug("Verified hash page at level %d, now want %s:%*phN\n",
			 level - 1, params->hash_alg->name, hsize, want_hash);
	}

	/* Finally, verify the data page */
	err = fsverity_hash_page(params, inode, req, data_page, real_hash);
	if (err)
		goto out;
	err = cmp_hashes(vi, want_hash, real_hash, index, -1);
out:
	for (; level > 0; level--)
		put_page(hpages[level - 1]);

	return err == 0;
}