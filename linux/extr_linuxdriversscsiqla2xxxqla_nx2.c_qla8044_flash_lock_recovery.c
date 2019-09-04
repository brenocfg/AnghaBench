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
struct scsi_qla_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 scalar_t__ qla8044_flash_lock (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qla8044_flash_unlock (struct scsi_qla_host*) ; 

__attribute__((used)) static
void qla8044_flash_lock_recovery(struct scsi_qla_host *vha)
{

	if (qla8044_flash_lock(vha)) {
		/* Someone else is holding the lock. */
		ql_log(ql_log_warn, vha, 0xb120, "Resetting flash_lock\n");
	}

	/*
	 * Either we got the lock, or someone
	 * else died while holding it.
	 * In either case, unlock.
	 */
	qla8044_flash_unlock(vha);
}