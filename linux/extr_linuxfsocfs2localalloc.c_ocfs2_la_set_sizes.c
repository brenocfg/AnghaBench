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
struct super_block {int dummy; } ;
struct ocfs2_super {void* local_alloc_default_bits; void* local_alloc_bits; struct super_block* sb; } ;

/* Variables and functions */
 unsigned int ocfs2_clusters_to_megabytes (struct super_block*,int) ; 
 unsigned int ocfs2_la_default_mb (struct ocfs2_super*) ; 
 int ocfs2_local_alloc_size (struct super_block*) ; 
 void* ocfs2_megabytes_to_clusters (struct super_block*,int) ; 
 int /*<<< orphan*/  trace_ocfs2_la_set_sizes (int,unsigned int,unsigned int) ; 

void ocfs2_la_set_sizes(struct ocfs2_super *osb, int requested_mb)
{
	struct super_block *sb = osb->sb;
	unsigned int la_default_mb = ocfs2_la_default_mb(osb);
	unsigned int la_max_mb;

	la_max_mb = ocfs2_clusters_to_megabytes(sb,
						ocfs2_local_alloc_size(sb) * 8);

	trace_ocfs2_la_set_sizes(requested_mb, la_max_mb, la_default_mb);

	if (requested_mb == -1) {
		/* No user request - use defaults */
		osb->local_alloc_default_bits =
			ocfs2_megabytes_to_clusters(sb, la_default_mb);
	} else if (requested_mb > la_max_mb) {
		/* Request is too big, we give the maximum available */
		osb->local_alloc_default_bits =
			ocfs2_megabytes_to_clusters(sb, la_max_mb);
	} else {
		osb->local_alloc_default_bits =
			ocfs2_megabytes_to_clusters(sb, requested_mb);
	}

	osb->local_alloc_bits = osb->local_alloc_default_bits;
}