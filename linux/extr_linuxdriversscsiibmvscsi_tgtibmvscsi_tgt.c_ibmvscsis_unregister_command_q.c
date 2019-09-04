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
struct TYPE_2__ {int /*<<< orphan*/  unit_id; } ;
struct scsi_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  intr_lock; int /*<<< orphan*/  flags; TYPE_1__ dds; } ;

/* Variables and functions */
 long ADAPT_SUCCESS ; 
 long ERROR ; 
#define  H_BUSY 137 
#define  H_HARDWARE 136 
#define  H_LONG_BUSY_ORDER_100_MSEC 135 
#define  H_LONG_BUSY_ORDER_100_SEC 134 
#define  H_LONG_BUSY_ORDER_10_MSEC 133 
#define  H_LONG_BUSY_ORDER_10_SEC 132 
#define  H_LONG_BUSY_ORDER_1_MSEC 131 
#define  H_LONG_BUSY_ORDER_1_SEC 130 
#define  H_PARAMETER 129 
#define  H_SUCCESS 128 
 int /*<<< orphan*/  PREP_FOR_SUSPEND_FLAGS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,long,long) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 long h_free_crq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssleep (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static long ibmvscsis_unregister_command_q(struct scsi_info *vscsi)
{
	long qrc;
	long rc = ADAPT_SUCCESS;
	int ticks = 0;

	do {
		qrc = h_free_crq(vscsi->dds.unit_id);
		switch (qrc) {
		case H_SUCCESS:
			spin_lock_bh(&vscsi->intr_lock);
			vscsi->flags &= ~PREP_FOR_SUSPEND_FLAGS;
			spin_unlock_bh(&vscsi->intr_lock);
			break;

		case H_HARDWARE:
		case H_PARAMETER:
			dev_err(&vscsi->dev, "unregister_command_q: error from h_free_crq %ld\n",
				qrc);
			rc = ERROR;
			break;

		case H_BUSY:
		case H_LONG_BUSY_ORDER_1_MSEC:
			/* msleep not good for small values */
			usleep_range(1000, 2000);
			ticks += 1;
			break;
		case H_LONG_BUSY_ORDER_10_MSEC:
			usleep_range(10000, 20000);
			ticks += 10;
			break;
		case H_LONG_BUSY_ORDER_100_MSEC:
			msleep(100);
			ticks += 100;
			break;
		case H_LONG_BUSY_ORDER_1_SEC:
			ssleep(1);
			ticks += 1000;
			break;
		case H_LONG_BUSY_ORDER_10_SEC:
			ssleep(10);
			ticks += 10000;
			break;
		case H_LONG_BUSY_ORDER_100_SEC:
			ssleep(100);
			ticks += 100000;
			break;
		default:
			dev_err(&vscsi->dev, "unregister_command_q: unknown error %ld from h_free_crq\n",
				qrc);
			rc = ERROR;
			break;
		}

		/*
		 * dont wait more then 300 seconds
		 * ticks are in milliseconds more or less
		 */
		if (ticks > 300000 && qrc != H_SUCCESS) {
			rc = ERROR;
			dev_err(&vscsi->dev, "Excessive wait for h_free_crq\n");
		}
	} while (qrc != H_SUCCESS && rc == ADAPT_SUCCESS);

	dev_dbg(&vscsi->dev, "Freeing CRQ: phyp rc %ld, rc %ld\n", qrc, rc);

	return rc;
}