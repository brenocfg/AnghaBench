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
struct xattr_iter {scalar_t__ ofs; int /*<<< orphan*/ * page; int /*<<< orphan*/  kaddr; int /*<<< orphan*/  blkaddr; int /*<<< orphan*/  sb; } ;

/* Variables and functions */
 scalar_t__ EROFS_BLKSIZ ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ erofs_blknr (scalar_t__) ; 
 scalar_t__ erofs_blkoff (scalar_t__) ; 
 int /*<<< orphan*/ * erofs_get_meta_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmap_atomic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xattr_iter_end (struct xattr_iter*,int) ; 

__attribute__((used)) static inline int xattr_iter_fixup(struct xattr_iter *it)
{
	if (it->ofs < EROFS_BLKSIZ)
		return 0;

	xattr_iter_end(it, true);

	it->blkaddr += erofs_blknr(it->ofs);

	it->page = erofs_get_meta_page(it->sb, it->blkaddr);
	if (IS_ERR(it->page)) {
		int err = PTR_ERR(it->page);

		it->page = NULL;
		return err;
	}

	it->kaddr = kmap_atomic(it->page);
	it->ofs = erofs_blkoff(it->ofs);
	return 0;
}