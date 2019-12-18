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
struct slink_front {char* symname; } ;
struct page {TYPE_1__* mapping; } ;
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_ino; } ;
struct file {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct affs_sb_info {char* s_prefix; int /*<<< orphan*/  symlink_lock; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 struct affs_sb_info* AFFS_SB (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int /*<<< orphan*/  SetPageError (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 struct buffer_head* affs_bread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  affs_brelse (struct buffer_head*) ; 
 char* page_address (struct page*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strchr (char*,char) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int affs_symlink_readpage(struct file *file, struct page *page)
{
	struct buffer_head *bh;
	struct inode *inode = page->mapping->host;
	char *link = page_address(page);
	struct slink_front *lf;
	int			 i, j;
	char			 c;
	char			 lc;

	pr_debug("get_link(ino=%lu)\n", inode->i_ino);

	bh = affs_bread(inode->i_sb, inode->i_ino);
	if (!bh)
		goto fail;
	i  = 0;
	j  = 0;
	lf = (struct slink_front *)bh->b_data;
	lc = 0;

	if (strchr(lf->symname,':')) {	/* Handle assign or volume name */
		struct affs_sb_info *sbi = AFFS_SB(inode->i_sb);
		char *pf;
		spin_lock(&sbi->symlink_lock);
		pf = sbi->s_prefix ? sbi->s_prefix : "/";
		while (i < 1023 && (c = pf[i]))
			link[i++] = c;
		spin_unlock(&sbi->symlink_lock);
		while (i < 1023 && lf->symname[j] != ':')
			link[i++] = lf->symname[j++];
		if (i < 1023)
			link[i++] = '/';
		j++;
		lc = '/';
	}
	while (i < 1023 && (c = lf->symname[j])) {
		if (c == '/' && lc == '/' && i < 1020) {	/* parent dir */
			link[i++] = '.';
			link[i++] = '.';
		}
		link[i++] = c;
		lc = c;
		j++;
	}
	link[i] = '\0';
	affs_brelse(bh);
	SetPageUptodate(page);
	unlock_page(page);
	return 0;
fail:
	SetPageError(page);
	unlock_page(page);
	return -EIO;
}