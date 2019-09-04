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
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_sb; } ;
typedef  int /*<<< orphan*/  erofs_blk_t ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 struct page* erofs_get_meta_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct page *
erofs_get_inline_page(struct inode *inode,
		      erofs_blk_t blkaddr)
{
	return erofs_get_meta_page(inode->i_sb,
		blkaddr, S_ISDIR(inode->i_mode));
}