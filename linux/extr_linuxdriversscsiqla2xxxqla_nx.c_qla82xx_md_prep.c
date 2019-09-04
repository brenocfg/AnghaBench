#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct qla_hw_data {int md_template_size; int md_dump_size; int /*<<< orphan*/ * md_tmplt_hdr; int /*<<< orphan*/  md_tmplt_hdr_dma; TYPE_1__* pdev; } ;
struct TYPE_11__ {struct qla_hw_data* hw; } ;
typedef  TYPE_2__ scsi_qla_host_t ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_QLA8044 (struct qla_hw_data*) ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_2__*,int,char*) ; 
 int /*<<< orphan*/  ql_dbg_p3p ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_2__*,int,char*,int,...) ; 
 int /*<<< orphan*/  ql_log_info ; 
 int qla8044_md_get_template (TYPE_2__*) ; 
 int qla82xx_md_alloc (TYPE_2__*) ; 
 int qla82xx_md_get_template (TYPE_2__*) ; 
 int qla82xx_md_get_template_size (TYPE_2__*) ; 

void
qla82xx_md_prep(scsi_qla_host_t *vha)
{
	struct qla_hw_data *ha = vha->hw;
	int rval;

	/* Get Minidump template size */
	rval = qla82xx_md_get_template_size(vha);
	if (rval == QLA_SUCCESS) {
		ql_log(ql_log_info, vha, 0xb04a,
		    "MiniDump Template size obtained (%d KB)\n",
		    ha->md_template_size / 1024);

		/* Get Minidump template */
		if (IS_QLA8044(ha))
			rval = qla8044_md_get_template(vha);
		else
			rval = qla82xx_md_get_template(vha);

		if (rval == QLA_SUCCESS) {
			ql_dbg(ql_dbg_p3p, vha, 0xb04b,
			    "MiniDump Template obtained\n");

			/* Allocate memory for minidump */
			rval = qla82xx_md_alloc(vha);
			if (rval == QLA_SUCCESS)
				ql_log(ql_log_info, vha, 0xb04c,
				    "MiniDump memory allocated (%d KB)\n",
				    ha->md_dump_size / 1024);
			else {
				ql_log(ql_log_info, vha, 0xb04d,
				    "Free MiniDump template: %p, size: (%d KB)\n",
				    ha->md_tmplt_hdr,
				    ha->md_template_size / 1024);
				dma_free_coherent(&ha->pdev->dev,
				    ha->md_template_size,
				    ha->md_tmplt_hdr, ha->md_tmplt_hdr_dma);
				ha->md_tmplt_hdr = NULL;
			}

		}
	}
}