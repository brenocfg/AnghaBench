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
typedef  int u32 ;
struct super_block {int s_blocksize_bits; } ;
struct qnx6_sb_info {TYPE_1__* longfile; } ;
struct qnx6_long_filename {int dummy; } ;
struct qnx6_long_dir_entry {int /*<<< orphan*/  de_long_inode; } ;
struct page {int dummy; } ;
struct address_space {int dummy; } ;
struct TYPE_2__ {struct address_space* i_mapping; } ;

/* Variables and functions */
 struct qnx6_long_filename* ERR_CAST (struct page*) ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 struct qnx6_sb_info* QNX6_SB (struct super_block*) ; 
 int fs32_to_cpu (struct qnx6_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmap (struct page*) ; 
 int page_address (struct page*) ; 
 struct page* read_mapping_page (struct address_space*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct qnx6_long_filename *qnx6_longname(struct super_block *sb,
					 struct qnx6_long_dir_entry *de,
					 struct page **p)
{
	struct qnx6_sb_info *sbi = QNX6_SB(sb);
	u32 s = fs32_to_cpu(sbi, de->de_long_inode); /* in block units */
	u32 n = s >> (PAGE_SHIFT - sb->s_blocksize_bits); /* in pages */
	/* within page */
	u32 offs = (s << sb->s_blocksize_bits) & ~PAGE_MASK;
	struct address_space *mapping = sbi->longfile->i_mapping;
	struct page *page = read_mapping_page(mapping, n, NULL);
	if (IS_ERR(page))
		return ERR_CAST(page);
	kmap(*p = page);
	return (struct qnx6_long_filename *)(page_address(page) + offs);
}