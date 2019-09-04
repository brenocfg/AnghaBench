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
typedef  int u8 ;
struct snic_abort_stats {int /*<<< orphan*/  fail; int /*<<< orphan*/  io_not_found; int /*<<< orphan*/  fw_tmo; } ;
struct TYPE_2__ {struct snic_abort_stats abts; } ;
struct snic {int /*<<< orphan*/  shost; TYPE_1__ s_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNIC_SCSI_DBG (int /*<<< orphan*/ ,char*) ; 
#define  SNIC_STAT_IO_NOT_FOUND 130 
#define  SNIC_STAT_IO_SUCCESS 129 
#define  SNIC_STAT_TIMEOUT 128 
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
snic_update_abort_stats(struct snic *snic, u8 cmpl_stat)
{
	struct snic_abort_stats *abt_stats = &snic->s_stats.abts;

	SNIC_SCSI_DBG(snic->shost, "Updating Abort stats.\n");

	switch (cmpl_stat) {
	case  SNIC_STAT_IO_SUCCESS:
		break;

	case SNIC_STAT_TIMEOUT:
		atomic64_inc(&abt_stats->fw_tmo);
		break;

	case SNIC_STAT_IO_NOT_FOUND:
		atomic64_inc(&abt_stats->io_not_found);
		break;

	default:
		atomic64_inc(&abt_stats->fail);
		break;
	}
}