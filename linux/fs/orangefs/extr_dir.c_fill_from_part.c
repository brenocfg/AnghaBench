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
struct orangefs_readdir_response_s {int dummy; } ;
struct orangefs_khandle {int dummy; } ;
struct orangefs_dir_part {int len; } ;
struct dir_context {int pos; } ;
typedef  int loff_t ;
typedef  int __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DT_UNKNOWN ; 
 int PART_MASK ; 
 int /*<<< orphan*/  dir_emit (struct dir_context*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  orangefs_khandle_to_ino (struct orangefs_khandle*) ; 

__attribute__((used)) static int fill_from_part(struct orangefs_dir_part *part,
    struct dir_context *ctx)
{
	const int offset = sizeof(struct orangefs_readdir_response_s);
	struct orangefs_khandle *khandle;
	__u32 *len, padlen;
	loff_t i;
	char *s;
	i = ctx->pos & ~PART_MASK;

	/* The file offset from userspace is too large. */
	if (i > part->len)
		return 1;

	/*
	 * If the seek pointer is positioned just before an entry it
	 * should find the next entry.
	 */
	if (i % 8)
		i = i + (8 - i%8)%8;

	while (i < part->len) {
		if (part->len < i + sizeof *len)
			break;
		len = (void *)part + offset + i;
		/*
		 * len is the size of the string itself.  padlen is the
		 * total size of the encoded string.
		 */
		padlen = (sizeof *len + *len + 1) +
		    (8 - (sizeof *len + *len + 1)%8)%8;
		if (part->len < i + padlen + sizeof *khandle)
			goto next;
		s = (void *)part + offset + i + sizeof *len;
		if (s[*len] != 0)
			goto next;
		khandle = (void *)part + offset + i + padlen;
		if (!dir_emit(ctx, s, *len,
		    orangefs_khandle_to_ino(khandle),
		    DT_UNKNOWN))
			return 0;
		i += padlen + sizeof *khandle;
		i = i + (8 - i%8)%8;
		BUG_ON(i > part->len);
		ctx->pos = (ctx->pos & PART_MASK) | i;
		continue;
next:
		i += 8;
	}
	return 1;
}