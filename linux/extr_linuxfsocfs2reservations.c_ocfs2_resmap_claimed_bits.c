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
typedef  int u32 ;
struct ocfs2_reservation_map {int dummy; } ;
struct ocfs2_alloc_reservation {int r_start; int r_last_start; int r_last_len; int /*<<< orphan*/  r_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ocfs2_adjust_resv_from_alloc (struct ocfs2_reservation_map*,struct ocfs2_alloc_reservation*,int,unsigned int) ; 
 int /*<<< orphan*/  ocfs2_check_resmap (struct ocfs2_reservation_map*) ; 
 scalar_t__ ocfs2_resmap_disabled (struct ocfs2_reservation_map*) ; 
 int /*<<< orphan*/  ocfs2_resv_empty (struct ocfs2_alloc_reservation*) ; 
 unsigned int ocfs2_resv_end (struct ocfs2_alloc_reservation*) ; 
 int /*<<< orphan*/  ocfs2_resv_mark_lru (struct ocfs2_reservation_map*,struct ocfs2_alloc_reservation*) ; 
 int /*<<< orphan*/  resv_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_ocfs2_resmap_claimed_bits_begin (int,unsigned int,int,int,unsigned int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  trace_ocfs2_resmap_claimed_bits_end (int,unsigned int,int /*<<< orphan*/ ,int,int) ; 

void ocfs2_resmap_claimed_bits(struct ocfs2_reservation_map *resmap,
			       struct ocfs2_alloc_reservation *resv,
			       u32 cstart, u32 clen)
{
	unsigned int cend = cstart + clen - 1;

	if (resmap == NULL || ocfs2_resmap_disabled(resmap))
		return;

	if (resv == NULL)
		return;

	BUG_ON(cstart != resv->r_start);

	spin_lock(&resv_lock);

	trace_ocfs2_resmap_claimed_bits_begin(cstart, cend, clen, resv->r_start,
					      ocfs2_resv_end(resv), resv->r_len,
					      resv->r_last_start,
					      resv->r_last_len);

	BUG_ON(cstart < resv->r_start);
	BUG_ON(cstart > ocfs2_resv_end(resv));
	BUG_ON(cend > ocfs2_resv_end(resv));

	ocfs2_adjust_resv_from_alloc(resmap, resv, cstart, cend);
	resv->r_last_start = cstart;
	resv->r_last_len = clen;

	/*
	 * May have been discarded above from
	 * ocfs2_adjust_resv_from_alloc().
	 */
	if (!ocfs2_resv_empty(resv))
		ocfs2_resv_mark_lru(resmap, resv);

	trace_ocfs2_resmap_claimed_bits_end(resv->r_start, ocfs2_resv_end(resv),
					    resv->r_len, resv->r_last_start,
					    resv->r_last_len);

	ocfs2_check_resmap(resmap);

	spin_unlock(&resv_lock);
}