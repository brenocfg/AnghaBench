#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct scsi_qla_host {int dummy; } ;
struct qla_hw_data {TYPE_4__* pdev; } ;
struct link_statistics {int dummy; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  jiffies_at_last_reset; } ;
struct TYPE_6__ {TYPE_5__ qla_stats; TYPE_5__ fc_host_stat; struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_0 ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_FWI2_CAPABLE (struct qla_hw_data*) ; 
 struct link_statistics* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,struct link_statistics*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_jiffies_64 () ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 struct scsi_qla_host* pci_get_drvdata (TYPE_4__*) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_1__*,int,char*) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int /*<<< orphan*/  qla24xx_get_isp_stats (struct scsi_qla_host*,struct link_statistics*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static void
qla2x00_reset_host_stats(struct Scsi_Host *shost)
{
	scsi_qla_host_t *vha = shost_priv(shost);
	struct qla_hw_data *ha = vha->hw;
	struct scsi_qla_host *base_vha = pci_get_drvdata(ha->pdev);
	struct link_statistics *stats;
	dma_addr_t stats_dma;

	memset(&vha->qla_stats, 0, sizeof(vha->qla_stats));
	memset(&vha->fc_host_stat, 0, sizeof(vha->fc_host_stat));

	vha->qla_stats.jiffies_at_last_reset = get_jiffies_64();

	if (IS_FWI2_CAPABLE(ha)) {
		stats = dma_alloc_coherent(&ha->pdev->dev,
		    sizeof(*stats), &stats_dma, GFP_KERNEL);
		if (!stats) {
			ql_log(ql_log_warn, vha, 0x70d7,
			    "Failed to allocate memory for stats.\n");
			return;
		}

		/* reset firmware statistics */
		qla24xx_get_isp_stats(base_vha, stats, stats_dma, BIT_0);

		dma_free_coherent(&ha->pdev->dev, sizeof(*stats),
		    stats, stats_dma);
	}
}