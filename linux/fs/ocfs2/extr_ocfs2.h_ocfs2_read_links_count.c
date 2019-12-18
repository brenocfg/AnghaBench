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
typedef  unsigned int u32 ;
struct ocfs2_dinode {int i_dyn_features; int /*<<< orphan*/  i_links_count_hi; int /*<<< orphan*/  i_links_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCFS2_INDEXED_DIR_FL ; 
 unsigned int OCFS2_LINKS_HI_SHIFT ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int ocfs2_read_links_count(struct ocfs2_dinode *di)
{
	u32 nlink = le16_to_cpu(di->i_links_count);
	u32 hi = le16_to_cpu(di->i_links_count_hi);

	if (di->i_dyn_features & cpu_to_le16(OCFS2_INDEXED_DIR_FL))
		nlink |= (hi << OCFS2_LINKS_HI_SHIFT);

	return nlink;
}