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
struct iomap_readpage_ctx {int cur_page_in_bio; int /*<<< orphan*/ * cur_page; int /*<<< orphan*/  pages; } ;
struct iomap {int dummy; } ;
struct inode {int dummy; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/ * iomap_next_page (struct inode*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__*) ; 
 scalar_t__ iomap_readpage_actor (struct inode*,scalar_t__,scalar_t__,struct iomap_readpage_ctx*,struct iomap*) ; 
 scalar_t__ offset_in_page (scalar_t__) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_page (int /*<<< orphan*/ *) ; 

__attribute__((used)) static loff_t
iomap_readpages_actor(struct inode *inode, loff_t pos, loff_t length,
		void *data, struct iomap *iomap)
{
	struct iomap_readpage_ctx *ctx = data;
	loff_t done, ret;

	for (done = 0; done < length; done += ret) {
		if (ctx->cur_page && offset_in_page(pos + done) == 0) {
			if (!ctx->cur_page_in_bio)
				unlock_page(ctx->cur_page);
			put_page(ctx->cur_page);
			ctx->cur_page = NULL;
		}
		if (!ctx->cur_page) {
			ctx->cur_page = iomap_next_page(inode, ctx->pages,
					pos, length, &done);
			if (!ctx->cur_page)
				break;
			ctx->cur_page_in_bio = false;
		}
		ret = iomap_readpage_actor(inode, pos + done, length - done,
				ctx, iomap);
	}

	return done;
}