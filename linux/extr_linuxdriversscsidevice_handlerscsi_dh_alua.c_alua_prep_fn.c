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
struct scsi_device {struct alua_dh_data* handler_data; } ;
struct request {int /*<<< orphan*/  rq_flags; } ;
struct alua_port_group {unsigned char state; } ;
struct alua_dh_data {int /*<<< orphan*/  pg; } ;

/* Variables and functions */
 int BLKPREP_DEFER ; 
 int BLKPREP_KILL ; 
 int BLKPREP_OK ; 
 int /*<<< orphan*/  RQF_QUIET ; 
 unsigned char SCSI_ACCESS_STATE_ACTIVE ; 
 unsigned char SCSI_ACCESS_STATE_LBA ; 
 unsigned char SCSI_ACCESS_STATE_OPTIMAL ; 
 unsigned char SCSI_ACCESS_STATE_TRANSITIONING ; 
 struct alua_port_group* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int alua_prep_fn(struct scsi_device *sdev, struct request *req)
{
	struct alua_dh_data *h = sdev->handler_data;
	struct alua_port_group *pg;
	unsigned char state = SCSI_ACCESS_STATE_OPTIMAL;
	int ret = BLKPREP_OK;

	rcu_read_lock();
	pg = rcu_dereference(h->pg);
	if (pg)
		state = pg->state;
	rcu_read_unlock();
	if (state == SCSI_ACCESS_STATE_TRANSITIONING)
		ret = BLKPREP_DEFER;
	else if (state != SCSI_ACCESS_STATE_OPTIMAL &&
		 state != SCSI_ACCESS_STATE_ACTIVE &&
		 state != SCSI_ACCESS_STATE_LBA) {
		ret = BLKPREP_KILL;
		req->rq_flags |= RQF_QUIET;
	}
	return ret;

}