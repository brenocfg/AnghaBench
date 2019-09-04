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
struct scsi_sense_hdr {int dummy; } ;
struct scsi_device {int dummy; } ;
struct alua_port_group {int tpgs; int state; int flags; int /*<<< orphan*/  group_id; int /*<<< orphan*/  pref; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALUA_DH_NAME ; 
 int ALUA_OPTIMIZE_STPG ; 
 scalar_t__ DRIVER_ERROR ; 
 int /*<<< orphan*/  KERN_INFO ; 
#define  SCSI_ACCESS_STATE_ACTIVE 133 
#define  SCSI_ACCESS_STATE_OFFLINE 132 
#define  SCSI_ACCESS_STATE_OPTIMAL 131 
#define  SCSI_ACCESS_STATE_STANDBY 130 
#define  SCSI_ACCESS_STATE_TRANSITIONING 129 
#define  SCSI_ACCESS_STATE_UNAVAILABLE 128 
 int SCSI_DH_DEV_TEMP_BUSY ; 
 int SCSI_DH_IO ; 
 int SCSI_DH_NOSYS ; 
 int SCSI_DH_OK ; 
 int SCSI_DH_RETRY ; 
 int TPGS_MODE_EXPLICIT ; 
 int TPGS_MODE_IMPLICIT ; 
 scalar_t__ driver_byte (int) ; 
 int /*<<< orphan*/  scsi_print_sense_hdr (struct scsi_device*,int /*<<< orphan*/ ,struct scsi_sense_hdr*) ; 
 int /*<<< orphan*/  scsi_sense_valid (struct scsi_sense_hdr*) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*,int /*<<< orphan*/ ,...) ; 
 int submit_stpg (struct scsi_device*,int /*<<< orphan*/ ,struct scsi_sense_hdr*) ; 

__attribute__((used)) static unsigned alua_stpg(struct scsi_device *sdev, struct alua_port_group *pg)
{
	int retval;
	struct scsi_sense_hdr sense_hdr;

	if (!(pg->tpgs & TPGS_MODE_EXPLICIT)) {
		/* Only implicit ALUA supported, retry */
		return SCSI_DH_RETRY;
	}
	switch (pg->state) {
	case SCSI_ACCESS_STATE_OPTIMAL:
		return SCSI_DH_OK;
	case SCSI_ACCESS_STATE_ACTIVE:
		if ((pg->flags & ALUA_OPTIMIZE_STPG) &&
		    !pg->pref &&
		    (pg->tpgs & TPGS_MODE_IMPLICIT))
			return SCSI_DH_OK;
		break;
	case SCSI_ACCESS_STATE_STANDBY:
	case SCSI_ACCESS_STATE_UNAVAILABLE:
		break;
	case SCSI_ACCESS_STATE_OFFLINE:
		return SCSI_DH_IO;
	case SCSI_ACCESS_STATE_TRANSITIONING:
		break;
	default:
		sdev_printk(KERN_INFO, sdev,
			    "%s: stpg failed, unhandled TPGS state %d",
			    ALUA_DH_NAME, pg->state);
		return SCSI_DH_NOSYS;
	}
	retval = submit_stpg(sdev, pg->group_id, &sense_hdr);

	if (retval) {
		if (!scsi_sense_valid(&sense_hdr)) {
			sdev_printk(KERN_INFO, sdev,
				    "%s: stpg failed, result %d",
				    ALUA_DH_NAME, retval);
			if (driver_byte(retval) == DRIVER_ERROR)
				return SCSI_DH_DEV_TEMP_BUSY;
		} else {
			sdev_printk(KERN_INFO, sdev, "%s: stpg failed\n",
				    ALUA_DH_NAME);
			scsi_print_sense_hdr(sdev, ALUA_DH_NAME, &sense_hdr);
		}
	}
	/* Retry RTPG */
	return SCSI_DH_RETRY;
}