#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct page {int dummy; } ;
struct minix_sb_info {char* s_dirsize; scalar_t__ s_version; int /*<<< orphan*/  s_namelen; } ;
struct inode {struct super_block* i_sb; } ;
struct TYPE_5__ {char* name; int len; } ;
struct dentry {int /*<<< orphan*/  d_parent; TYPE_1__ d_name; } ;
struct TYPE_6__ {char* name; int /*<<< orphan*/  inode; } ;
typedef  TYPE_2__ minix_dirent ;
struct TYPE_7__ {char* name; int /*<<< orphan*/  inode; } ;
typedef  TYPE_3__ minix3_dirent ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct page*) ; 
 scalar_t__ MINIX_V3 ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 struct page* dir_get_page (struct inode*,unsigned long) ; 
 unsigned long dir_pages (struct inode*) ; 
 int /*<<< orphan*/  dir_put_page (struct page*) ; 
 int minix_last_byte (struct inode*,unsigned long) ; 
 char* minix_next_entry (char*,struct minix_sb_info*) ; 
 struct minix_sb_info* minix_sb (struct super_block*) ; 
 scalar_t__ namecompare (int,int /*<<< orphan*/ ,char const*,char*) ; 
 scalar_t__ page_address (struct page*) ; 

minix_dirent *minix_find_entry(struct dentry *dentry, struct page **res_page)
{
	const char * name = dentry->d_name.name;
	int namelen = dentry->d_name.len;
	struct inode * dir = d_inode(dentry->d_parent);
	struct super_block * sb = dir->i_sb;
	struct minix_sb_info * sbi = minix_sb(sb);
	unsigned long n;
	unsigned long npages = dir_pages(dir);
	struct page *page = NULL;
	char *p;

	char *namx;
	__u32 inumber;
	*res_page = NULL;

	for (n = 0; n < npages; n++) {
		char *kaddr, *limit;

		page = dir_get_page(dir, n);
		if (IS_ERR(page))
			continue;

		kaddr = (char*)page_address(page);
		limit = kaddr + minix_last_byte(dir, n) - sbi->s_dirsize;
		for (p = kaddr; p <= limit; p = minix_next_entry(p, sbi)) {
			if (sbi->s_version == MINIX_V3) {
				minix3_dirent *de3 = (minix3_dirent *)p;
				namx = de3->name;
				inumber = de3->inode;
 			} else {
				minix_dirent *de = (minix_dirent *)p;
				namx = de->name;
				inumber = de->inode;
			}
			if (!inumber)
				continue;
			if (namecompare(namelen, sbi->s_namelen, name, namx))
				goto found;
		}
		dir_put_page(page);
	}
	return NULL;

found:
	*res_page = page;
	return (minix_dirent *)p;
}