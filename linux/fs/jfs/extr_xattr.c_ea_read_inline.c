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
struct jfs_inode_info {int /*<<< orphan*/  i_inline_ea; int /*<<< orphan*/  ea; } ;
struct jfs_ea_list {scalar_t__ size; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 struct jfs_inode_info* JFS_IP (struct inode*) ; 
 int le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (struct jfs_ea_list*,int /*<<< orphan*/ ,int) ; 
 int sizeDXD (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ea_read_inline(struct inode *ip, struct jfs_ea_list *ealist)
{
	struct jfs_inode_info *ji = JFS_IP(ip);
	int ea_size = sizeDXD(&ji->ea);

	if (ea_size == 0) {
		ealist->size = 0;
		return 0;
	}

	/* Sanity Check */
	if ((sizeDXD(&ji->ea) > sizeof (ji->i_inline_ea)))
		return -EIO;
	if (le32_to_cpu(((struct jfs_ea_list *) &ji->i_inline_ea)->size)
	    != ea_size)
		return -EIO;

	memcpy(ealist, ji->i_inline_ea, ea_size);
	return 0;
}