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
typedef  int u64 ;
struct ocfs2_super {int s_clustersize; } ;
struct inode {int /*<<< orphan*/  i_sb; struct address_space* i_mapping; } ;
struct address_space {int dummy; } ;
typedef  int loff_t ;

/* Variables and functions */
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_align_bytes_to_clusters (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  truncate_inode_pages_range (struct address_space*,int,int) ; 
 int /*<<< orphan*/  unmap_mapping_range (struct address_space*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocfs2_truncate_cluster_pages(struct inode *inode, u64 byte_start,
					 u64 byte_len)
{
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	loff_t start, end;
	struct address_space *mapping = inode->i_mapping;

	start = (loff_t)ocfs2_align_bytes_to_clusters(inode->i_sb, byte_start);
	end = byte_start + byte_len;
	end = end & ~(osb->s_clustersize - 1);

	if (start < end) {
		unmap_mapping_range(mapping, start, end - start, 0);
		truncate_inode_pages_range(mapping, start, end - 1);
	}
}