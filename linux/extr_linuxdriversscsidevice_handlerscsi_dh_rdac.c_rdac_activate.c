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
struct scsi_device {struct rdac_dh_data* handler_data; } ;
struct rdac_dh_data {int mode; int /*<<< orphan*/  preferred; int /*<<< orphan*/  lun_state; } ;
typedef  int /*<<< orphan*/  (* activate_complete ) (void*,int) ;

/* Variables and functions */
 int /*<<< orphan*/  RDAC_LUN_UNOWNED ; 
#define  RDAC_MODE 129 
#define  RDAC_MODE_IOSHIP 128 
 int /*<<< orphan*/  RDAC_PREFERRED ; 
 int SCSI_DH_OK ; 
 int check_ownership (struct scsi_device*,struct rdac_dh_data*) ; 
 int queue_mode_select (struct scsi_device*,int /*<<< orphan*/  (*) (void*,int),void*) ; 

__attribute__((used)) static int rdac_activate(struct scsi_device *sdev,
			activate_complete fn, void *data)
{
	struct rdac_dh_data *h = sdev->handler_data;
	int err = SCSI_DH_OK;
	int act = 0;

	err = check_ownership(sdev, h);
	if (err != SCSI_DH_OK)
		goto done;

	switch (h->mode) {
	case RDAC_MODE:
		if (h->lun_state == RDAC_LUN_UNOWNED)
			act = 1;
		break;
	case RDAC_MODE_IOSHIP:
		if ((h->lun_state == RDAC_LUN_UNOWNED) &&
		    (h->preferred == RDAC_PREFERRED))
			act = 1;
		break;
	default:
		break;
	}

	if (act) {
		err = queue_mode_select(sdev, fn, data);
		if (err == SCSI_DH_OK)
			return 0;
	}
done:
	if (fn)
		fn(data, err);
	return 0;
}