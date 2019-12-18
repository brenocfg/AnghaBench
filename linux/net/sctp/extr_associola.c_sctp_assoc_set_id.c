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
struct sctp_association {scalar_t__ assoc_id; } ;
typedef  scalar_t__ sctp_assoc_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOWAIT ; 
 scalar_t__ SCTP_ALL_ASSOC ; 
 int gfpflags_allow_blocking (int /*<<< orphan*/ ) ; 
 int idr_alloc_cyclic (int /*<<< orphan*/ *,struct sctp_association*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload_end () ; 
 int /*<<< orphan*/  sctp_assocs_id ; 
 int /*<<< orphan*/  sctp_assocs_id_lock ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int sctp_assoc_set_id(struct sctp_association *asoc, gfp_t gfp)
{
	bool preload = gfpflags_allow_blocking(gfp);
	int ret;

	/* If the id is already assigned, keep it. */
	if (asoc->assoc_id)
		return 0;

	if (preload)
		idr_preload(gfp);
	spin_lock_bh(&sctp_assocs_id_lock);
	/* 0, 1, 2 are used as SCTP_FUTURE_ASSOC, SCTP_CURRENT_ASSOC and
	 * SCTP_ALL_ASSOC, so an available id must be > SCTP_ALL_ASSOC.
	 */
	ret = idr_alloc_cyclic(&sctp_assocs_id, asoc, SCTP_ALL_ASSOC + 1, 0,
			       GFP_NOWAIT);
	spin_unlock_bh(&sctp_assocs_id_lock);
	if (preload)
		idr_preload_end();
	if (ret < 0)
		return ret;

	asoc->assoc_id = (sctp_assoc_t)ret;
	return 0;
}