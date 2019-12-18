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
struct sysv_dir_entry {char* name; int /*<<< orphan*/  inode; } ;
struct super_block {int dummy; } ;
struct page {int dummy; } ;
struct inode {unsigned long i_size; struct super_block* i_sb; } ;
struct file {int dummy; } ;
struct dir_context {unsigned long pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  DT_UNKNOWN ; 
 scalar_t__ IS_ERR (struct page*) ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 unsigned long SYSV_DIRSIZE ; 
 int /*<<< orphan*/  SYSV_NAMELEN ; 
 int /*<<< orphan*/  SYSV_SB (struct super_block*) ; 
 int /*<<< orphan*/  dir_emit (struct dir_context*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct page* dir_get_page (struct inode*,unsigned long) ; 
 unsigned long dir_pages (struct inode*) ; 
 int /*<<< orphan*/  dir_put_page (struct page*) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  fs16_to_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ page_address (struct page*) ; 
 int /*<<< orphan*/  strnlen (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sysv_readdir(struct file *file, struct dir_context *ctx)
{
	unsigned long pos = ctx->pos;
	struct inode *inode = file_inode(file);
	struct super_block *sb = inode->i_sb;
	unsigned long npages = dir_pages(inode);
	unsigned offset;
	unsigned long n;

	ctx->pos = pos = (pos + SYSV_DIRSIZE-1) & ~(SYSV_DIRSIZE-1);
	if (pos >= inode->i_size)
		return 0;

	offset = pos & ~PAGE_MASK;
	n = pos >> PAGE_SHIFT;

	for ( ; n < npages; n++, offset = 0) {
		char *kaddr, *limit;
		struct sysv_dir_entry *de;
		struct page *page = dir_get_page(inode, n);

		if (IS_ERR(page))
			continue;
		kaddr = (char *)page_address(page);
		de = (struct sysv_dir_entry *)(kaddr+offset);
		limit = kaddr + PAGE_SIZE - SYSV_DIRSIZE;
		for ( ;(char*)de <= limit; de++, ctx->pos += sizeof(*de)) {
			char *name = de->name;

			if (!de->inode)
				continue;

			if (!dir_emit(ctx, name, strnlen(name,SYSV_NAMELEN),
					fs16_to_cpu(SYSV_SB(sb), de->inode),
					DT_UNKNOWN)) {
				dir_put_page(page);
				return 0;
			}
		}
		dir_put_page(page);
	}
	return 0;
}