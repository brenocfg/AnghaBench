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
typedef  int uint16_t ;
struct scsi_qla_host {int /*<<< orphan*/  req_q_count; struct queue_entry* request_ptr; } ;
struct queue_entry {int dummy; } ;

/* Variables and functions */
 int QLA_ERROR ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  memset (struct queue_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qla4xxx_advance_req_ring_ptr (struct scsi_qla_host*) ; 
 scalar_t__ qla4xxx_space_in_req_ring (struct scsi_qla_host*,int) ; 

__attribute__((used)) static int qla4xxx_get_req_pkt(struct scsi_qla_host *ha,
			       struct queue_entry **queue_entry)
{
	uint16_t req_cnt = 1;

	if (qla4xxx_space_in_req_ring(ha, req_cnt)) {
		*queue_entry = ha->request_ptr;
		memset(*queue_entry, 0, sizeof(**queue_entry));

		qla4xxx_advance_req_ring_ptr(ha);
		ha->req_q_count -= req_cnt;
		return QLA_SUCCESS;
	}

	return QLA_ERROR;
}