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
struct TYPE_2__ {int /*<<< orphan*/  topo; } ;
struct intel_ntb_dev {int hwerr_flags; int /*<<< orphan*/  unsafe_flags; TYPE_1__ ntb; scalar_t__ unsafe_flags_ignore; } ;

/* Variables and functions */
 int NTB_HWERR_SB01BASE_LOCKUP ; 
 int NTB_HWERR_SDOORBELL_LOCKUP ; 
 int /*<<< orphan*/  NTB_UNSAFE_DB ; 
 int /*<<< orphan*/  NTB_UNSAFE_SPAD ; 
 int /*<<< orphan*/  ntb_topo_is_b2b (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ndev_reset_unsafe_flags(struct intel_ntb_dev *ndev)
{
	ndev->unsafe_flags = 0;
	ndev->unsafe_flags_ignore = 0;

	/* Only B2B has a workaround to avoid SDOORBELL */
	if (ndev->hwerr_flags & NTB_HWERR_SDOORBELL_LOCKUP)
		if (!ntb_topo_is_b2b(ndev->ntb.topo))
			ndev->unsafe_flags |= NTB_UNSAFE_DB;

	/* No low level workaround to avoid SB01BASE */
	if (ndev->hwerr_flags & NTB_HWERR_SB01BASE_LOCKUP) {
		ndev->unsafe_flags |= NTB_UNSAFE_DB;
		ndev->unsafe_flags |= NTB_UNSAFE_SPAD;
	}
}