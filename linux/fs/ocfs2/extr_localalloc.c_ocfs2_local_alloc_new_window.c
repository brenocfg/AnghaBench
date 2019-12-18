#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_super {int /*<<< orphan*/  osb_la_resmap; int /*<<< orphan*/  la_last_gd; int /*<<< orphan*/  osb_lock; int /*<<< orphan*/  local_alloc_bits; TYPE_1__* local_alloc_bh; } ;
struct ocfs2_local_alloc {void* la_bm_off; int /*<<< orphan*/  la_bitmap; int /*<<< orphan*/  la_size; } ;
struct TYPE_5__ {void* i_total; scalar_t__ i_used; } ;
struct TYPE_6__ {TYPE_2__ bitmap1; } ;
struct ocfs2_dinode {TYPE_3__ id1; } ;
struct ocfs2_alloc_context {int /*<<< orphan*/  ac_last_group; int /*<<< orphan*/  ac_bits_wanted; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_4__ {scalar_t__ b_data; } ;

/* Variables and functions */
 int ENOSPC ; 
 scalar_t__ OCFS2_LA_DISABLED ; 
 int /*<<< orphan*/  OCFS2_LA_EVENT_FRAGMENTED ; 
 struct ocfs2_local_alloc* OCFS2_LOCAL_ALLOC (struct ocfs2_dinode*) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (void*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_claim_clusters (int /*<<< orphan*/ *,struct ocfs2_alloc_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ocfs2_recalc_la_window (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_resmap_restart (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_ocfs2_local_alloc_new_window (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ocfs2_local_alloc_new_window_result (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_local_alloc_new_window(struct ocfs2_super *osb,
					handle_t *handle,
					struct ocfs2_alloc_context *ac)
{
	int status = 0;
	u32 cluster_off, cluster_count;
	struct ocfs2_dinode *alloc = NULL;
	struct ocfs2_local_alloc *la;

	alloc = (struct ocfs2_dinode *) osb->local_alloc_bh->b_data;
	la = OCFS2_LOCAL_ALLOC(alloc);

	trace_ocfs2_local_alloc_new_window(
		le32_to_cpu(alloc->id1.bitmap1.i_total),
		osb->local_alloc_bits);

	/* Instruct the allocation code to try the most recently used
	 * cluster group. We'll re-record the group used this pass
	 * below. */
	ac->ac_last_group = osb->la_last_gd;

	/* we used the generic suballoc reserve function, but we set
	 * everything up nicely, so there's no reason why we can't use
	 * the more specific cluster api to claim bits. */
	status = ocfs2_claim_clusters(handle, ac, osb->local_alloc_bits,
				      &cluster_off, &cluster_count);
	if (status == -ENOSPC) {
retry_enospc:
		/*
		 * Note: We could also try syncing the journal here to
		 * allow use of any free bits which the current
		 * transaction can't give us access to. --Mark
		 */
		if (ocfs2_recalc_la_window(osb, OCFS2_LA_EVENT_FRAGMENTED) ==
		    OCFS2_LA_DISABLED)
			goto bail;

		ac->ac_bits_wanted = osb->local_alloc_bits;
		status = ocfs2_claim_clusters(handle, ac,
					      osb->local_alloc_bits,
					      &cluster_off,
					      &cluster_count);
		if (status == -ENOSPC)
			goto retry_enospc;
		/*
		 * We only shrunk the *minimum* number of in our
		 * request - it's entirely possible that the allocator
		 * might give us more than we asked for.
		 */
		if (status == 0) {
			spin_lock(&osb->osb_lock);
			osb->local_alloc_bits = cluster_count;
			spin_unlock(&osb->osb_lock);
		}
	}
	if (status < 0) {
		if (status != -ENOSPC)
			mlog_errno(status);
		goto bail;
	}

	osb->la_last_gd = ac->ac_last_group;

	la->la_bm_off = cpu_to_le32(cluster_off);
	alloc->id1.bitmap1.i_total = cpu_to_le32(cluster_count);
	/* just in case... In the future when we find space ourselves,
	 * we don't have to get all contiguous -- but we'll have to
	 * set all previously used bits in bitmap and update
	 * la_bits_set before setting the bits in the main bitmap. */
	alloc->id1.bitmap1.i_used = 0;
	memset(OCFS2_LOCAL_ALLOC(alloc)->la_bitmap, 0,
	       le16_to_cpu(la->la_size));

	ocfs2_resmap_restart(&osb->osb_la_resmap, cluster_count,
			     OCFS2_LOCAL_ALLOC(alloc)->la_bitmap);

	trace_ocfs2_local_alloc_new_window_result(
		OCFS2_LOCAL_ALLOC(alloc)->la_bm_off,
		le32_to_cpu(alloc->id1.bitmap1.i_total));

bail:
	if (status)
		mlog_errno(status);
	return status;
}