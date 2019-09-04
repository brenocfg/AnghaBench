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
struct ocfs2_super {int s_feature_ro_compat; } ;

/* Variables and functions */
 int OCFS2_FEATURE_RO_COMPAT_UNWRITTEN ; 
 int /*<<< orphan*/  ocfs2_sparse_alloc (struct ocfs2_super*) ; 

__attribute__((used)) static inline int ocfs2_writes_unwritten_extents(struct ocfs2_super *osb)
{
	/*
	 * Support for sparse files is a pre-requisite
	 */
	if (!ocfs2_sparse_alloc(osb))
		return 0;

	if (osb->s_feature_ro_compat & OCFS2_FEATURE_RO_COMPAT_UNWRITTEN)
		return 1;
	return 0;
}