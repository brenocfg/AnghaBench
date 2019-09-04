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
struct page {scalar_t__ mapping; } ;
struct TYPE_2__ {struct page* control_page; } ;
struct fscrypt_ctx {TYPE_1__ w; } ;

/* Variables and functions */
 int /*<<< orphan*/  fscrypt_restore_control_page (struct page*) ; 
 scalar_t__ page_private (struct page*) ; 

void fscrypt_pullback_bio_page(struct page **page, bool restore)
{
	struct fscrypt_ctx *ctx;
	struct page *bounce_page;

	/* The bounce data pages are unmapped. */
	if ((*page)->mapping)
		return;

	/* The bounce data page is unmapped. */
	bounce_page = *page;
	ctx = (struct fscrypt_ctx *)page_private(bounce_page);

	/* restore control page */
	*page = ctx->w.control_page;

	if (restore)
		fscrypt_restore_control_page(bounce_page);
}