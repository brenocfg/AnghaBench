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
struct qedf_ctx {int /*<<< orphan*/  dbg_ctx; int /*<<< orphan*/  num_offloads; } ;

/* Variables and functions */
 int /*<<< orphan*/  QEDF_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  QEDF_LOG_DISC ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 

void qedf_wait_for_upload(struct qedf_ctx *qedf)
{
	while (1) {
		if (atomic_read(&qedf->num_offloads))
			QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC,
			    "Waiting for all uploads to complete.\n");
		else
			break;
		msleep(500);
	}
}