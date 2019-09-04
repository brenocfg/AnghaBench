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
typedef  size_t u32 ;
struct gfs2_inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  no_addr; } ;
struct gfs2_dirent {scalar_t__ de_cookie; int /*<<< orphan*/  de_type; TYPE_1__ de_inum; int /*<<< orphan*/  de_name_len; } ;
struct dir_context {scalar_t__ pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compare_dents ; 
 int /*<<< orphan*/  dir_emit (struct dir_context*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sort (struct gfs2_dirent**,size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_filldir_main(struct gfs2_inode *dip, struct dir_context *ctx,
			   struct gfs2_dirent **darr, u32 entries,
			   u32 sort_start, int *copied)
{
	const struct gfs2_dirent *dent, *dent_next;
	u64 off, off_next;
	unsigned int x, y;
	int run = 0;

	if (sort_start < entries)
		sort(&darr[sort_start], entries - sort_start,
		     sizeof(struct gfs2_dirent *), compare_dents, NULL);

	dent_next = darr[0];
	off_next = dent_next->de_cookie;

	for (x = 0, y = 1; x < entries; x++, y++) {
		dent = dent_next;
		off = off_next;

		if (y < entries) {
			dent_next = darr[y];
			off_next = dent_next->de_cookie;

			if (off < ctx->pos)
				continue;
			ctx->pos = off;

			if (off_next == off) {
				if (*copied && !run)
					return 1;
				run = 1;
			} else
				run = 0;
		} else {
			if (off < ctx->pos)
				continue;
			ctx->pos = off;
		}

		if (!dir_emit(ctx, (const char *)(dent + 1),
				be16_to_cpu(dent->de_name_len),
				be64_to_cpu(dent->de_inum.no_addr),
				be16_to_cpu(dent->de_type)))
			return 1;

		*copied = 1;
	}

	/* Increment the ctx->pos by one, so the next time we come into the
	   do_filldir fxn, we get the next entry instead of the last one in the
	   current leaf */

	ctx->pos++;

	return 0;
}