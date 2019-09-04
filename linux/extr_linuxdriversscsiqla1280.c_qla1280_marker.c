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
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  u8 ;
struct scsi_qla_host {int dummy; } ;
struct mrk_entry {scalar_t__ entry_status; int /*<<< orphan*/  modifier; void* target; void* lun; int /*<<< orphan*/  entry_type; } ;

/* Variables and functions */
 int BIT_7 ; 
 int /*<<< orphan*/  ENTER (char*) ; 
 int /*<<< orphan*/  LEAVE (char*) ; 
 int /*<<< orphan*/  MARKER_TYPE ; 
 int /*<<< orphan*/  qla1280_isp_cmd (struct scsi_qla_host*) ; 
 scalar_t__ qla1280_req_pkt (struct scsi_qla_host*) ; 

__attribute__((used)) static void
qla1280_marker(struct scsi_qla_host *ha, int bus, int id, int lun, u8 type)
{
	struct mrk_entry *pkt;

	ENTER("qla1280_marker");

	/* Get request packet. */
	if ((pkt = (struct mrk_entry *) qla1280_req_pkt(ha))) {
		pkt->entry_type = MARKER_TYPE;
		pkt->lun = (uint8_t) lun;
		pkt->target = (uint8_t) (bus ? (id | BIT_7) : id);
		pkt->modifier = type;
		pkt->entry_status = 0;

		/* Issue command to ISP */
		qla1280_isp_cmd(ha);
	}

	LEAVE("qla1280_marker");
}