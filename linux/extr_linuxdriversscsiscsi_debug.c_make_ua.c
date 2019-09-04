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
struct sdebug_dev_info {int /*<<< orphan*/  uas_bm; } ;
struct scsi_cmnd {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_RESET_ASCQ ; 
 int /*<<< orphan*/  CAPACITY_CHANGED_ASCQ ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LUNS_CHANGED_ASCQ ; 
 int /*<<< orphan*/  MICROCODE_CHANGED_ASCQ ; 
 int /*<<< orphan*/  MICROCODE_CHANGED_WO_RESET_ASCQ ; 
 int /*<<< orphan*/  MODE_CHANGED_ASCQ ; 
 int /*<<< orphan*/  POWER_ON_RESET_ASCQ ; 
 int SDEBUG_NUM_UAS ; 
#define  SDEBUG_UA_BUS_RESET 134 
#define  SDEBUG_UA_CAPACITY_CHANGED 133 
#define  SDEBUG_UA_LUNS_CHANGED 132 
#define  SDEBUG_UA_MICROCODE_CHANGED 131 
#define  SDEBUG_UA_MICROCODE_CHANGED_WO_RESET 130 
#define  SDEBUG_UA_MODE_CHANGED 129 
#define  SDEBUG_UA_POR 128 
 int /*<<< orphan*/  TARGET_CHANGED_ASC ; 
 int /*<<< orphan*/  UA_CHANGED_ASC ; 
 int /*<<< orphan*/  UA_RESET_ASC ; 
 int /*<<< orphan*/  UNIT_ATTENTION ; 
 int check_condition_result ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_luns_changed_on_target (struct sdebug_dev_info*) ; 
 int find_first_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mk_sense_buffer (struct scsi_cmnd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  my_name ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int sdebug_scsi_level ; 
 scalar_t__ sdebug_verbose ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int make_ua(struct scsi_cmnd *scp, struct sdebug_dev_info *devip)
{
	int k;

	k = find_first_bit(devip->uas_bm, SDEBUG_NUM_UAS);
	if (k != SDEBUG_NUM_UAS) {
		const char *cp = NULL;

		switch (k) {
		case SDEBUG_UA_POR:
			mk_sense_buffer(scp, UNIT_ATTENTION, UA_RESET_ASC,
					POWER_ON_RESET_ASCQ);
			if (sdebug_verbose)
				cp = "power on reset";
			break;
		case SDEBUG_UA_BUS_RESET:
			mk_sense_buffer(scp, UNIT_ATTENTION, UA_RESET_ASC,
					BUS_RESET_ASCQ);
			if (sdebug_verbose)
				cp = "bus reset";
			break;
		case SDEBUG_UA_MODE_CHANGED:
			mk_sense_buffer(scp, UNIT_ATTENTION, UA_CHANGED_ASC,
					MODE_CHANGED_ASCQ);
			if (sdebug_verbose)
				cp = "mode parameters changed";
			break;
		case SDEBUG_UA_CAPACITY_CHANGED:
			mk_sense_buffer(scp, UNIT_ATTENTION, UA_CHANGED_ASC,
					CAPACITY_CHANGED_ASCQ);
			if (sdebug_verbose)
				cp = "capacity data changed";
			break;
		case SDEBUG_UA_MICROCODE_CHANGED:
			mk_sense_buffer(scp, UNIT_ATTENTION,
					TARGET_CHANGED_ASC,
					MICROCODE_CHANGED_ASCQ);
			if (sdebug_verbose)
				cp = "microcode has been changed";
			break;
		case SDEBUG_UA_MICROCODE_CHANGED_WO_RESET:
			mk_sense_buffer(scp, UNIT_ATTENTION,
					TARGET_CHANGED_ASC,
					MICROCODE_CHANGED_WO_RESET_ASCQ);
			if (sdebug_verbose)
				cp = "microcode has been changed without reset";
			break;
		case SDEBUG_UA_LUNS_CHANGED:
			/*
			 * SPC-3 behavior is to report a UNIT ATTENTION with
			 * ASC/ASCQ REPORTED LUNS DATA HAS CHANGED on every LUN
			 * on the target, until a REPORT LUNS command is
			 * received.  SPC-4 behavior is to report it only once.
			 * NOTE:  sdebug_scsi_level does not use the same
			 * values as struct scsi_device->scsi_level.
			 */
			if (sdebug_scsi_level >= 6)	/* SPC-4 and above */
				clear_luns_changed_on_target(devip);
			mk_sense_buffer(scp, UNIT_ATTENTION,
					TARGET_CHANGED_ASC,
					LUNS_CHANGED_ASCQ);
			if (sdebug_verbose)
				cp = "reported luns data has changed";
			break;
		default:
			pr_warn("unexpected unit attention code=%d\n", k);
			if (sdebug_verbose)
				cp = "unknown";
			break;
		}
		clear_bit(k, devip->uas_bm);
		if (sdebug_verbose)
			sdev_printk(KERN_INFO, scp->device,
				   "%s reports: Unit attention: %s\n",
				   my_name, cp);
		return check_condition_result;
	}
	return 0;
}