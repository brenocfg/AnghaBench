#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  scsi_qla_host_t ;
struct TYPE_4__ {int /*<<< orphan*/  entry_capture_mask; int /*<<< orphan*/  driver_flags; } ;
struct TYPE_5__ {TYPE_1__ d_ctrl; int /*<<< orphan*/  entry_type; } ;
typedef  TYPE_2__ qla82xx_md_entry_hdr_t ;

/* Variables and functions */
 int /*<<< orphan*/  QLA82XX_DBG_SKIPPED_FLAG ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_p3p ; 

__attribute__((used)) static void
qla82xx_mark_entry_skipped(scsi_qla_host_t *vha,
	qla82xx_md_entry_hdr_t *entry_hdr, int index)
{
	entry_hdr->d_ctrl.driver_flags |= QLA82XX_DBG_SKIPPED_FLAG;
	ql_dbg(ql_dbg_p3p, vha, 0xb036,
	    "Skipping entry[%d]: "
	    "ETYPE[0x%x]-ELEVEL[0x%x]\n",
	    index, entry_hdr->entry_type,
	    entry_hdr->d_ctrl.entry_capture_mask);
}