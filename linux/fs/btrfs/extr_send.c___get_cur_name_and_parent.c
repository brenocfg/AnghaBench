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
typedef  scalar_t__ u64 ;
struct send_ctx {scalar_t__ send_progress; int /*<<< orphan*/  parent_root; int /*<<< orphan*/  send_root; } ;
struct name_cache_entry {int need_later_update; scalar_t__ parent_ino; scalar_t__ parent_gen; int ret; int /*<<< orphan*/  name; scalar_t__ name_len; scalar_t__ gen; scalar_t__ ino; } ;
struct fs_path {scalar_t__ start; scalar_t__ end; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int did_overwrite_ref (struct send_ctx*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int fs_path_add (struct fs_path*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ fs_path_len (struct fs_path*) ; 
 int /*<<< orphan*/  fs_path_reset (struct fs_path*) ; 
 int gen_unique_name (struct send_ctx*,scalar_t__,scalar_t__,struct fs_path*) ; 
 int get_first_ref (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,scalar_t__*,struct fs_path*) ; 
 int is_inode_existent (struct send_ctx*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct name_cache_entry*) ; 
 struct name_cache_entry* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  name_cache_clean_unused (struct send_ctx*) ; 
 int /*<<< orphan*/  name_cache_delete (struct send_ctx*,struct name_cache_entry*) ; 
 int name_cache_insert (struct send_ctx*,struct name_cache_entry*) ; 
 struct name_cache_entry* name_cache_search (struct send_ctx*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  name_cache_used (struct send_ctx*,struct name_cache_entry*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int __get_cur_name_and_parent(struct send_ctx *sctx,
				     u64 ino, u64 gen,
				     u64 *parent_ino,
				     u64 *parent_gen,
				     struct fs_path *dest)
{
	int ret;
	int nce_ret;
	struct name_cache_entry *nce = NULL;

	/*
	 * First check if we already did a call to this function with the same
	 * ino/gen. If yes, check if the cache entry is still up-to-date. If yes
	 * return the cached result.
	 */
	nce = name_cache_search(sctx, ino, gen);
	if (nce) {
		if (ino < sctx->send_progress && nce->need_later_update) {
			name_cache_delete(sctx, nce);
			kfree(nce);
			nce = NULL;
		} else {
			name_cache_used(sctx, nce);
			*parent_ino = nce->parent_ino;
			*parent_gen = nce->parent_gen;
			ret = fs_path_add(dest, nce->name, nce->name_len);
			if (ret < 0)
				goto out;
			ret = nce->ret;
			goto out;
		}
	}

	/*
	 * If the inode is not existent yet, add the orphan name and return 1.
	 * This should only happen for the parent dir that we determine in
	 * __record_new_ref
	 */
	ret = is_inode_existent(sctx, ino, gen);
	if (ret < 0)
		goto out;

	if (!ret) {
		ret = gen_unique_name(sctx, ino, gen, dest);
		if (ret < 0)
			goto out;
		ret = 1;
		goto out_cache;
	}

	/*
	 * Depending on whether the inode was already processed or not, use
	 * send_root or parent_root for ref lookup.
	 */
	if (ino < sctx->send_progress)
		ret = get_first_ref(sctx->send_root, ino,
				    parent_ino, parent_gen, dest);
	else
		ret = get_first_ref(sctx->parent_root, ino,
				    parent_ino, parent_gen, dest);
	if (ret < 0)
		goto out;

	/*
	 * Check if the ref was overwritten by an inode's ref that was processed
	 * earlier. If yes, treat as orphan and return 1.
	 */
	ret = did_overwrite_ref(sctx, *parent_ino, *parent_gen, ino, gen,
			dest->start, dest->end - dest->start);
	if (ret < 0)
		goto out;
	if (ret) {
		fs_path_reset(dest);
		ret = gen_unique_name(sctx, ino, gen, dest);
		if (ret < 0)
			goto out;
		ret = 1;
	}

out_cache:
	/*
	 * Store the result of the lookup in the name cache.
	 */
	nce = kmalloc(sizeof(*nce) + fs_path_len(dest) + 1, GFP_KERNEL);
	if (!nce) {
		ret = -ENOMEM;
		goto out;
	}

	nce->ino = ino;
	nce->gen = gen;
	nce->parent_ino = *parent_ino;
	nce->parent_gen = *parent_gen;
	nce->name_len = fs_path_len(dest);
	nce->ret = ret;
	strcpy(nce->name, dest->start);

	if (ino < sctx->send_progress)
		nce->need_later_update = 0;
	else
		nce->need_later_update = 1;

	nce_ret = name_cache_insert(sctx, nce);
	if (nce_ret < 0)
		ret = nce_ret;
	name_cache_clean_unused(sctx);

out:
	return ret;
}