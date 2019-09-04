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
struct dir_entry {int /*<<< orphan*/  name_len; int /*<<< orphan*/  type; int /*<<< orphan*/  ino; int /*<<< orphan*/  offset; } ;
struct dir_context {scalar_t__ pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  dir_emit (struct dir_context*,char*,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ get_unaligned (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btrfs_filldir(void *addr, int entries, struct dir_context *ctx)
{
	while (entries--) {
		struct dir_entry *entry = addr;
		char *name = (char *)(entry + 1);

		ctx->pos = get_unaligned(&entry->offset);
		if (!dir_emit(ctx, name, get_unaligned(&entry->name_len),
					 get_unaligned(&entry->ino),
					 get_unaligned(&entry->type)))
			return 1;
		addr += sizeof(struct dir_entry) +
			get_unaligned(&entry->name_len);
		ctx->pos++;
	}
	return 0;
}