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
struct page {int dummy; } ;
struct fscrypt_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPagePrivate (struct page*) ; 
 int /*<<< orphan*/  fscrypt_release_ctx (struct fscrypt_ctx*) ; 
 scalar_t__ page_private (struct page*) ; 
 int /*<<< orphan*/  set_page_private (struct page*,unsigned long) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

void fscrypt_restore_control_page(struct page *page)
{
	struct fscrypt_ctx *ctx;

	ctx = (struct fscrypt_ctx *)page_private(page);
	set_page_private(page, (unsigned long)NULL);
	ClearPagePrivate(page);
	unlock_page(page);
	fscrypt_release_ctx(ctx);
}