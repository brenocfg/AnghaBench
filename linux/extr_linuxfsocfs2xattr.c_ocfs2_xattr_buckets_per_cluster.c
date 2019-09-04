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
typedef  int u16 ;
struct ocfs2_super {int s_clustersize_bits; } ;

/* Variables and functions */
 int OCFS2_XATTR_BUCKET_SIZE ; 

__attribute__((used)) static inline u16 ocfs2_xattr_buckets_per_cluster(struct ocfs2_super *osb)
{
	return (1 << osb->s_clustersize_bits) / OCFS2_XATTR_BUCKET_SIZE;
}