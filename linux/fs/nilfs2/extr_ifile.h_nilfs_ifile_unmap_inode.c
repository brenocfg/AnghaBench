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
struct inode {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_page; } ;
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 int /*<<< orphan*/  kunmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void nilfs_ifile_unmap_inode(struct inode *ifile, ino_t ino,
					   struct buffer_head *ibh)
{
	kunmap(ibh->b_page);
}