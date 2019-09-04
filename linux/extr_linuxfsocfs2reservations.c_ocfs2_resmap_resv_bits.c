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
struct ocfs2_reservation_map {int dummy; } ;
struct ocfs2_alloc_reservation {int r_flags; int r_start; int r_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (scalar_t__) ; 
 int ENOSPC ; 
 int OCFS2_RESV_FLAG_TMP ; 
 scalar_t__ ocfs2_resmap_disabled (struct ocfs2_reservation_map*) ; 
 scalar_t__ ocfs2_resv_empty (struct ocfs2_alloc_reservation*) ; 
 int /*<<< orphan*/  ocfs2_resv_find_window (struct ocfs2_reservation_map*,struct ocfs2_alloc_reservation*,unsigned int) ; 
 unsigned int ocfs2_resv_window_bits (struct ocfs2_reservation_map*,struct ocfs2_alloc_reservation*) ; 
 int /*<<< orphan*/  resv_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_ocfs2_resmap_resv_bits (int,int) ; 

int ocfs2_resmap_resv_bits(struct ocfs2_reservation_map *resmap,
			   struct ocfs2_alloc_reservation *resv,
			   int *cstart, int *clen)
{
	if (resv == NULL || ocfs2_resmap_disabled(resmap))
		return -ENOSPC;

	spin_lock(&resv_lock);

	if (ocfs2_resv_empty(resv)) {
		/*
		 * We don't want to over-allocate for temporary
		 * windows. Otherwise, we run the risk of fragmenting the
		 * allocation space.
		 */
		unsigned int wanted = ocfs2_resv_window_bits(resmap, resv);

		if ((resv->r_flags & OCFS2_RESV_FLAG_TMP) || wanted < *clen)
			wanted = *clen;

		/*
		 * Try to get a window here. If it works, we must fall
		 * through and test the bitmap . This avoids some
		 * ping-ponging of windows due to non-reserved space
		 * being allocation before we initialize a window for
		 * that inode.
		 */
		ocfs2_resv_find_window(resmap, resv, wanted);
		trace_ocfs2_resmap_resv_bits(resv->r_start, resv->r_len);
	}

	BUG_ON(ocfs2_resv_empty(resv));

	*cstart = resv->r_start;
	*clen = resv->r_len;

	spin_unlock(&resv_lock);
	return 0;
}