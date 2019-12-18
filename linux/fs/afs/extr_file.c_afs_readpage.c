#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct page {TYPE_1__* mapping; } ;
struct key {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  cell; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 TYPE_2__* AFS_FS_S (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int PTR_ERR (struct key*) ; 
 struct key* afs_file_key (struct file*) ; 
 int afs_page_filler (struct key*,struct page*) ; 
 struct key* afs_request_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 

__attribute__((used)) static int afs_readpage(struct file *file, struct page *page)
{
	struct key *key;
	int ret;

	if (file) {
		key = afs_file_key(file);
		ASSERT(key != NULL);
		ret = afs_page_filler(key, page);
	} else {
		struct inode *inode = page->mapping->host;
		key = afs_request_key(AFS_FS_S(inode->i_sb)->cell);
		if (IS_ERR(key)) {
			ret = PTR_ERR(key);
		} else {
			ret = afs_page_filler(key, page);
			key_put(key);
		}
	}
	return ret;
}