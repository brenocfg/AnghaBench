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
struct super_block {int dummy; } ;
struct TYPE_2__ {int s_clustersize_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int OCFS2_MAX_CLUSTERSIZE ; 
 TYPE_1__* OCFS2_SB (struct super_block*) ; 

__attribute__((used)) static inline unsigned int ocfs2_megabytes_to_clusters(struct super_block *sb,
						       unsigned int megs)
{
	BUILD_BUG_ON(OCFS2_MAX_CLUSTERSIZE > 1048576);

	return megs << (20 - OCFS2_SB(sb)->s_clustersize_bits);
}