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
typedef  scalar_t__ ulong ;
struct inode {int i_size; int /*<<< orphan*/  i_mode; } ;
typedef  int loff_t ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ real_space_diff (struct inode*,int) ; 

__attribute__((used)) static inline loff_t to_real_used_space(struct inode *inode, ulong blocks,
					int sd_size)
{
	if (S_ISLNK(inode->i_mode) || S_ISDIR(inode->i_mode)) {
		return inode->i_size +
		    (loff_t) (real_space_diff(inode, sd_size));
	}
	return ((loff_t) real_space_diff(inode, sd_size)) +
	    (((loff_t) blocks) << 9);
}