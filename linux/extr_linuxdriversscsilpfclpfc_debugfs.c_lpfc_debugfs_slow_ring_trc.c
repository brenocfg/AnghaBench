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
typedef  int /*<<< orphan*/  uint32_t ;
struct lpfc_hba {int dummy; } ;

/* Variables and functions */

inline void
lpfc_debugfs_slow_ring_trc(struct lpfc_hba *phba, char *fmt,
	uint32_t data1, uint32_t data2, uint32_t data3)
{
#ifdef CONFIG_SCSI_LPFC_DEBUG_FS
	struct lpfc_debugfs_trc *dtp;
	int index;

	if (!lpfc_debugfs_enable || !lpfc_debugfs_max_slow_ring_trc ||
		!phba || !phba->slow_ring_trc)
		return;

	index = atomic_inc_return(&phba->slow_ring_trc_cnt) &
		(lpfc_debugfs_max_slow_ring_trc - 1);
	dtp = phba->slow_ring_trc + index;
	dtp->fmt = fmt;
	dtp->data1 = data1;
	dtp->data2 = data2;
	dtp->data3 = data3;
	dtp->seq_cnt = atomic_inc_return(&lpfc_debugfs_seq_trc_cnt);
	dtp->jif = jiffies;
#endif
	return;
}