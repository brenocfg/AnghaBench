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
struct ocfs2_inode_info {int /*<<< orphan*/  ip_lock; int /*<<< orphan*/  ip_extent_map; } ;
struct ocfs2_extent_map_item {unsigned int ei_cpos; unsigned int ei_phys; unsigned int ei_clusters; unsigned int ei_flags; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 struct ocfs2_inode_info* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  __ocfs2_extent_map_lookup (int /*<<< orphan*/ *,unsigned int,struct ocfs2_extent_map_item**) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_extent_map_lookup(struct inode *inode, unsigned int cpos,
				   unsigned int *phys, unsigned int *len,
				   unsigned int *flags)
{
	unsigned int coff;
	struct ocfs2_inode_info *oi = OCFS2_I(inode);
	struct ocfs2_extent_map_item *emi;

	spin_lock(&oi->ip_lock);

	__ocfs2_extent_map_lookup(&oi->ip_extent_map, cpos, &emi);
	if (emi) {
		coff = cpos - emi->ei_cpos;
		*phys = emi->ei_phys + coff;
		if (len)
			*len = emi->ei_clusters - coff;
		if (flags)
			*flags = emi->ei_flags;
	}

	spin_unlock(&oi->ip_lock);

	if (emi == NULL)
		return -ENOENT;

	return 0;
}