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
struct page {int dummy; } ;
struct inode {TYPE_2__* i_sb; } ;
typedef  struct page fscrypt_ctx ;
struct TYPE_3__ {int bi_sector; } ;
struct bio {scalar_t__ bi_status; TYPE_1__ bi_iter; } ;
typedef  int sector_t ;
typedef  int /*<<< orphan*/  pgoff_t ;
struct TYPE_4__ {int s_blocksize; int s_blocksize_bits; int /*<<< orphan*/  s_bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FS_ENCRYPT ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int PAGE_SIZE ; 
 int PTR_ERR (struct page*) ; 
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ZERO_PAGE (int /*<<< orphan*/ ) ; 
 int bio_add_page (struct bio*,struct page*,int,int /*<<< orphan*/ ) ; 
 struct bio* bio_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_set_op_attrs (struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct page* fscrypt_alloc_bounce_page (struct page*,int /*<<< orphan*/ ) ; 
 int fscrypt_do_page_crypto (struct inode const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct page*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct page* fscrypt_get_ctx (struct inode const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fscrypt_release_ctx (struct page*) ; 
 int submit_bio_wait (struct bio*) ; 

int fscrypt_zeroout_range(const struct inode *inode, pgoff_t lblk,
				sector_t pblk, unsigned int len)
{
	struct fscrypt_ctx *ctx;
	struct page *ciphertext_page = NULL;
	struct bio *bio;
	int ret, err = 0;

	BUG_ON(inode->i_sb->s_blocksize != PAGE_SIZE);

	ctx = fscrypt_get_ctx(inode, GFP_NOFS);
	if (IS_ERR(ctx))
		return PTR_ERR(ctx);

	ciphertext_page = fscrypt_alloc_bounce_page(ctx, GFP_NOWAIT);
	if (IS_ERR(ciphertext_page)) {
		err = PTR_ERR(ciphertext_page);
		goto errout;
	}

	while (len--) {
		err = fscrypt_do_page_crypto(inode, FS_ENCRYPT, lblk,
					     ZERO_PAGE(0), ciphertext_page,
					     PAGE_SIZE, 0, GFP_NOFS);
		if (err)
			goto errout;

		bio = bio_alloc(GFP_NOWAIT, 1);
		if (!bio) {
			err = -ENOMEM;
			goto errout;
		}
		bio_set_dev(bio, inode->i_sb->s_bdev);
		bio->bi_iter.bi_sector =
			pblk << (inode->i_sb->s_blocksize_bits - 9);
		bio_set_op_attrs(bio, REQ_OP_WRITE, 0);
		ret = bio_add_page(bio, ciphertext_page,
					inode->i_sb->s_blocksize, 0);
		if (ret != inode->i_sb->s_blocksize) {
			/* should never happen! */
			WARN_ON(1);
			bio_put(bio);
			err = -EIO;
			goto errout;
		}
		err = submit_bio_wait(bio);
		if (err == 0 && bio->bi_status)
			err = -EIO;
		bio_put(bio);
		if (err)
			goto errout;
		lblk++;
		pblk++;
	}
	err = 0;
errout:
	fscrypt_release_ctx(ctx);
	return err;
}