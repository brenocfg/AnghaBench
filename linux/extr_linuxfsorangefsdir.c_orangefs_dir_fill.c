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
struct orangefs_inode_s {int dummy; } ;
struct orangefs_dir_part {struct orangefs_dir_part* next; scalar_t__ len; } ;
struct orangefs_dir {int error; struct orangefs_dir_part* part; } ;
struct dir_context {int pos; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int PART_MASK ; 
 int PART_SHIFT ; 
 int fill_from_part (struct orangefs_dir_part*,struct dir_context*) ; 

__attribute__((used)) static int orangefs_dir_fill(struct orangefs_inode_s *oi,
    struct orangefs_dir *od, struct dentry *dentry,
    struct dir_context *ctx)
{
	struct orangefs_dir_part *part;
	size_t count;

	count = ((ctx->pos & PART_MASK) >> PART_SHIFT) - 1;

	part = od->part;
	while (part->next && count) {
		count--;
		part = part->next;
	}
	/* This means the userspace file offset is invalid. */
	if (count) {
		od->error = -EIO;
		return -EIO;
	}

	while (part && part->len) {
		int r;
		r = fill_from_part(part, ctx);
		if (r < 0) {
			od->error = r;
			return r;
		} else if (r == 0) {
			/* Userspace buffer is full. */
			break;
		} else {
			/*
			 * The part ran out of data.  Move to the next
			 * part. */
			ctx->pos = (ctx->pos & PART_MASK) +
			    (1 << PART_SHIFT);
			part = part->next;
		}
	}
	return 0;
}