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
struct iomap {scalar_t__ type; } ;
struct inode {int dummy; } ;
struct fiemap_ctx {struct iomap prev; int /*<<< orphan*/  fi; } ;
typedef  int loff_t ;

/* Variables and functions */
 scalar_t__ IOMAP_HOLE ; 
 int iomap_to_fiemap (int /*<<< orphan*/ ,struct iomap*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static loff_t
iomap_fiemap_actor(struct inode *inode, loff_t pos, loff_t length, void *data,
		struct iomap *iomap)
{
	struct fiemap_ctx *ctx = data;
	loff_t ret = length;

	if (iomap->type == IOMAP_HOLE)
		return length;

	ret = iomap_to_fiemap(ctx->fi, &ctx->prev, 0);
	ctx->prev = *iomap;
	switch (ret) {
	case 0:		/* success */
		return length;
	case 1:		/* extent array full */
		return 0;
	default:
		return ret;
	}
}