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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_6__ {struct page* control_page; } ;
struct page {TYPE_3__ w; } ;
struct inode {TYPE_2__* i_sb; } ;
struct fscrypt_ctx {TYPE_3__ w; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_5__ {TYPE_1__* s_cop; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct page* ERR_PTR (int) ; 
 int FS_CFLG_OWN_PAGES ; 
 unsigned int FS_CRYPTO_BLOCK_SIZE ; 
 int /*<<< orphan*/  FS_ENCRYPT ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int /*<<< orphan*/  SetPagePrivate (struct page*) ; 
 struct page* fscrypt_alloc_bounce_page (struct page*,int /*<<< orphan*/ ) ; 
 int fscrypt_do_page_crypto (struct inode const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct page*,struct page*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 struct page* fscrypt_get_ctx (struct inode const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fscrypt_release_ctx (struct page*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  set_page_private (struct page*,unsigned long) ; 

struct page *fscrypt_encrypt_page(const struct inode *inode,
				struct page *page,
				unsigned int len,
				unsigned int offs,
				u64 lblk_num, gfp_t gfp_flags)

{
	struct fscrypt_ctx *ctx;
	struct page *ciphertext_page = page;
	int err;

	BUG_ON(len % FS_CRYPTO_BLOCK_SIZE != 0);

	if (inode->i_sb->s_cop->flags & FS_CFLG_OWN_PAGES) {
		/* with inplace-encryption we just encrypt the page */
		err = fscrypt_do_page_crypto(inode, FS_ENCRYPT, lblk_num, page,
					     ciphertext_page, len, offs,
					     gfp_flags);
		if (err)
			return ERR_PTR(err);

		return ciphertext_page;
	}

	BUG_ON(!PageLocked(page));

	ctx = fscrypt_get_ctx(inode, gfp_flags);
	if (IS_ERR(ctx))
		return (struct page *)ctx;

	/* The encryption operation will require a bounce page. */
	ciphertext_page = fscrypt_alloc_bounce_page(ctx, gfp_flags);
	if (IS_ERR(ciphertext_page))
		goto errout;

	ctx->w.control_page = page;
	err = fscrypt_do_page_crypto(inode, FS_ENCRYPT, lblk_num,
				     page, ciphertext_page, len, offs,
				     gfp_flags);
	if (err) {
		ciphertext_page = ERR_PTR(err);
		goto errout;
	}
	SetPagePrivate(ciphertext_page);
	set_page_private(ciphertext_page, (unsigned long)ctx);
	lock_page(ciphertext_page);
	return ciphertext_page;

errout:
	fscrypt_release_ctx(ctx);
	return ciphertext_page;
}