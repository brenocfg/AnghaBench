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
struct dasd_device {TYPE_1__* cdev; } ;
struct dasd_ccw_req {int /*<<< orphan*/  refers; struct dasd_device* startdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_EER_PPRCSUSPEND ; 
 int ERRORLENGTH ; 
 int /*<<< orphan*/  dasd_eer_write (struct dasd_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char) ; 

__attribute__((used)) static void
dasd_3990_handle_env_data(struct dasd_ccw_req * erp, char *sense)
{

	struct dasd_device *device = erp->startdev;
	char msg_format = (sense[7] & 0xF0);
	char msg_no = (sense[7] & 0x0F);
	char errorstring[ERRORLENGTH];

	switch (msg_format) {
	case 0x00:		/* Format 0 - Program or System Checks */

		if (sense[1] & 0x10) {	/* check message to operator bit */

			switch (msg_no) {
			case 0x00:	/* No Message */
				break;
			case 0x01:
				dev_warn(&device->cdev->dev,
					    "FORMAT 0 - Invalid Command\n");
				break;
			case 0x02:
				dev_warn(&device->cdev->dev,
					    "FORMAT 0 - Invalid Command "
					    "Sequence\n");
				break;
			case 0x03:
				dev_warn(&device->cdev->dev,
					    "FORMAT 0 - CCW Count less than "
					    "required\n");
				break;
			case 0x04:
				dev_warn(&device->cdev->dev,
					    "FORMAT 0 - Invalid Parameter\n");
				break;
			case 0x05:
				dev_warn(&device->cdev->dev,
					    "FORMAT 0 - Diagnostic of Special"
					    " Command Violates File Mask\n");
				break;
			case 0x07:
				dev_warn(&device->cdev->dev,
					    "FORMAT 0 - Channel Returned with "
					    "Incorrect retry CCW\n");
				break;
			case 0x08:
				dev_warn(&device->cdev->dev,
					    "FORMAT 0 - Reset Notification\n");
				break;
			case 0x09:
				dev_warn(&device->cdev->dev,
					 "FORMAT 0 - Storage Path Restart\n");
				break;
			case 0x0A:
				dev_warn(&device->cdev->dev,
					    "FORMAT 0 - Channel requested "
					    "... %02x\n", sense[8]);
				break;
			case 0x0B:
				dev_warn(&device->cdev->dev,
					    "FORMAT 0 - Invalid Defective/"
					    "Alternate Track Pointer\n");
				break;
			case 0x0C:
				dev_warn(&device->cdev->dev,
					    "FORMAT 0 - DPS Installation "
					    "Check\n");
				break;
			case 0x0E:
				dev_warn(&device->cdev->dev,
					    "FORMAT 0 - Command Invalid on "
					    "Secondary Address\n");
				break;
			case 0x0F:
				dev_warn(&device->cdev->dev,
					    "FORMAT 0 - Status Not As "
					    "Required: reason %02x\n",
					 sense[8]);
				break;
			default:
				dev_warn(&device->cdev->dev,
					    "FORMAT 0 - Reserved\n");
			}
		} else {
			switch (msg_no) {
			case 0x00:	/* No Message */
				break;
			case 0x01:
				dev_warn(&device->cdev->dev,
					 "FORMAT 0 - Device Error "
					 "Source\n");
				break;
			case 0x02:
				dev_warn(&device->cdev->dev,
					    "FORMAT 0 - Reserved\n");
				break;
			case 0x03:
				dev_warn(&device->cdev->dev,
					    "FORMAT 0 - Device Fenced - "
					    "device = %02x\n", sense[4]);
				break;
			case 0x04:
				dev_warn(&device->cdev->dev,
					    "FORMAT 0 - Data Pinned for "
					    "Device\n");
				break;
			default:
				dev_warn(&device->cdev->dev,
					    "FORMAT 0 - Reserved\n");
			}
		}
		break;

	case 0x10:		/* Format 1 - Device Equipment Checks */
		switch (msg_no) {
		case 0x00:	/* No Message */
			break;
		case 0x01:
			dev_warn(&device->cdev->dev,
				    "FORMAT 1 - Device Status 1 not as "
				    "expected\n");
			break;
		case 0x03:
			dev_warn(&device->cdev->dev,
				    "FORMAT 1 - Index missing\n");
			break;
		case 0x04:
			dev_warn(&device->cdev->dev,
				 "FORMAT 1 - Interruption cannot be "
				 "reset\n");
			break;
		case 0x05:
			dev_warn(&device->cdev->dev,
				    "FORMAT 1 - Device did not respond to "
				    "selection\n");
			break;
		case 0x06:
			dev_warn(&device->cdev->dev,
				    "FORMAT 1 - Device check-2 error or Set "
				    "Sector is not complete\n");
			break;
		case 0x07:
			dev_warn(&device->cdev->dev,
				    "FORMAT 1 - Head address does not "
				    "compare\n");
			break;
		case 0x08:
			dev_warn(&device->cdev->dev,
				    "FORMAT 1 - Device status 1 not valid\n");
			break;
		case 0x09:
			dev_warn(&device->cdev->dev,
				    "FORMAT 1 - Device not ready\n");
			break;
		case 0x0A:
			dev_warn(&device->cdev->dev,
				    "FORMAT 1 - Track physical address did "
				    "not compare\n");
			break;
		case 0x0B:
			dev_warn(&device->cdev->dev,
				    "FORMAT 1 - Missing device address bit\n");
			break;
		case 0x0C:
			dev_warn(&device->cdev->dev,
				    "FORMAT 1 - Drive motor switch is off\n");
			break;
		case 0x0D:
			dev_warn(&device->cdev->dev,
				    "FORMAT 1 - Seek incomplete\n");
			break;
		case 0x0E:
			dev_warn(&device->cdev->dev,
				    "FORMAT 1 - Cylinder address did not "
				    "compare\n");
			break;
		case 0x0F:
			dev_warn(&device->cdev->dev,
				    "FORMAT 1 - Offset active cannot be "
				    "reset\n");
			break;
		default:
			dev_warn(&device->cdev->dev,
				    "FORMAT 1 - Reserved\n");
		}
		break;

	case 0x20:		/* Format 2 - 3990 Equipment Checks */
		switch (msg_no) {
		case 0x08:
			dev_warn(&device->cdev->dev,
				    "FORMAT 2 - 3990 check-2 error\n");
			break;
		case 0x0E:
			dev_warn(&device->cdev->dev,
				    "FORMAT 2 - Support facility errors\n");
			break;
		case 0x0F:
			dev_warn(&device->cdev->dev,
				 "FORMAT 2 - Microcode detected error "
				 "%02x\n",
				 sense[8]);
			break;
		default:
			dev_warn(&device->cdev->dev,
				    "FORMAT 2 - Reserved\n");
		}
		break;

	case 0x30:		/* Format 3 - 3990 Control Checks */
		switch (msg_no) {
		case 0x0F:
			dev_warn(&device->cdev->dev,
				    "FORMAT 3 - Allegiance terminated\n");
			break;
		default:
			dev_warn(&device->cdev->dev,
				    "FORMAT 3 - Reserved\n");
		}
		break;

	case 0x40:		/* Format 4 - Data Checks */
		switch (msg_no) {
		case 0x00:
			dev_warn(&device->cdev->dev,
				    "FORMAT 4 - Home address area error\n");
			break;
		case 0x01:
			dev_warn(&device->cdev->dev,
				    "FORMAT 4 - Count area error\n");
			break;
		case 0x02:
			dev_warn(&device->cdev->dev,
				    "FORMAT 4 - Key area error\n");
			break;
		case 0x03:
			dev_warn(&device->cdev->dev,
				    "FORMAT 4 - Data area error\n");
			break;
		case 0x04:
			dev_warn(&device->cdev->dev,
				    "FORMAT 4 - No sync byte in home address "
				    "area\n");
			break;
		case 0x05:
			dev_warn(&device->cdev->dev,
				    "FORMAT 4 - No sync byte in count address "
				    "area\n");
			break;
		case 0x06:
			dev_warn(&device->cdev->dev,
				    "FORMAT 4 - No sync byte in key area\n");
			break;
		case 0x07:
			dev_warn(&device->cdev->dev,
				    "FORMAT 4 - No sync byte in data area\n");
			break;
		case 0x08:
			dev_warn(&device->cdev->dev,
				    "FORMAT 4 - Home address area error; "
				    "offset active\n");
			break;
		case 0x09:
			dev_warn(&device->cdev->dev,
				    "FORMAT 4 - Count area error; offset "
				    "active\n");
			break;
		case 0x0A:
			dev_warn(&device->cdev->dev,
				    "FORMAT 4 - Key area error; offset "
				    "active\n");
			break;
		case 0x0B:
			dev_warn(&device->cdev->dev,
				    "FORMAT 4 - Data area error; "
				    "offset active\n");
			break;
		case 0x0C:
			dev_warn(&device->cdev->dev,
				    "FORMAT 4 - No sync byte in home "
				    "address area; offset active\n");
			break;
		case 0x0D:
			dev_warn(&device->cdev->dev,
				    "FORMAT 4 - No sync byte in count "
				    "address area; offset active\n");
			break;
		case 0x0E:
			dev_warn(&device->cdev->dev,
				    "FORMAT 4 - No sync byte in key area; "
				    "offset active\n");
			break;
		case 0x0F:
			dev_warn(&device->cdev->dev,
				    "FORMAT 4 - No sync byte in data area; "
				    "offset active\n");
			break;
		default:
			dev_warn(&device->cdev->dev,
				    "FORMAT 4 - Reserved\n");
		}
		break;

	case 0x50:  /* Format 5 - Data Check with displacement information */
		switch (msg_no) {
		case 0x00:
			dev_warn(&device->cdev->dev,
				    "FORMAT 5 - Data Check in the "
				    "home address area\n");
			break;
		case 0x01:
			dev_warn(&device->cdev->dev,
				 "FORMAT 5 - Data Check in the count "
				 "area\n");
			break;
		case 0x02:
			dev_warn(&device->cdev->dev,
				    "FORMAT 5 - Data Check in the key area\n");
			break;
		case 0x03:
			dev_warn(&device->cdev->dev,
				 "FORMAT 5 - Data Check in the data "
				 "area\n");
			break;
		case 0x08:
			dev_warn(&device->cdev->dev,
				    "FORMAT 5 - Data Check in the "
				    "home address area; offset active\n");
			break;
		case 0x09:
			dev_warn(&device->cdev->dev,
				    "FORMAT 5 - Data Check in the count area; "
				    "offset active\n");
			break;
		case 0x0A:
			dev_warn(&device->cdev->dev,
				    "FORMAT 5 - Data Check in the key area; "
				    "offset active\n");
			break;
		case 0x0B:
			dev_warn(&device->cdev->dev,
				    "FORMAT 5 - Data Check in the data area; "
				    "offset active\n");
			break;
		default:
			dev_warn(&device->cdev->dev,
				    "FORMAT 5 - Reserved\n");
		}
		break;

	case 0x60:  /* Format 6 - Usage Statistics/Overrun Errors */
		switch (msg_no) {
		case 0x00:
			dev_warn(&device->cdev->dev,
				    "FORMAT 6 - Overrun on channel A\n");
			break;
		case 0x01:
			dev_warn(&device->cdev->dev,
				    "FORMAT 6 - Overrun on channel B\n");
			break;
		case 0x02:
			dev_warn(&device->cdev->dev,
				    "FORMAT 6 - Overrun on channel C\n");
			break;
		case 0x03:
			dev_warn(&device->cdev->dev,
				    "FORMAT 6 - Overrun on channel D\n");
			break;
		case 0x04:
			dev_warn(&device->cdev->dev,
				    "FORMAT 6 - Overrun on channel E\n");
			break;
		case 0x05:
			dev_warn(&device->cdev->dev,
				    "FORMAT 6 - Overrun on channel F\n");
			break;
		case 0x06:
			dev_warn(&device->cdev->dev,
				    "FORMAT 6 - Overrun on channel G\n");
			break;
		case 0x07:
			dev_warn(&device->cdev->dev,
				    "FORMAT 6 - Overrun on channel H\n");
			break;
		default:
			dev_warn(&device->cdev->dev,
				    "FORMAT 6 - Reserved\n");
		}
		break;

	case 0x70:  /* Format 7 - Device Connection Control Checks */
		switch (msg_no) {
		case 0x00:
			dev_warn(&device->cdev->dev,
				    "FORMAT 7 - RCC initiated by a connection "
				    "check alert\n");
			break;
		case 0x01:
			dev_warn(&device->cdev->dev,
				    "FORMAT 7 - RCC 1 sequence not "
				    "successful\n");
			break;
		case 0x02:
			dev_warn(&device->cdev->dev,
				    "FORMAT 7 - RCC 1 and RCC 2 sequences not "
				    "successful\n");
			break;
		case 0x03:
			dev_warn(&device->cdev->dev,
				    "FORMAT 7 - Invalid tag-in during "
				    "selection sequence\n");
			break;
		case 0x04:
			dev_warn(&device->cdev->dev,
				    "FORMAT 7 - extra RCC required\n");
			break;
		case 0x05:
			dev_warn(&device->cdev->dev,
				    "FORMAT 7 - Invalid DCC selection "
				    "response or timeout\n");
			break;
		case 0x06:
			dev_warn(&device->cdev->dev,
				    "FORMAT 7 - Missing end operation; device "
				    "transfer complete\n");
			break;
		case 0x07:
			dev_warn(&device->cdev->dev,
				    "FORMAT 7 - Missing end operation; device "
				    "transfer incomplete\n");
			break;
		case 0x08:
			dev_warn(&device->cdev->dev,
				    "FORMAT 7 - Invalid tag-in for an "
				    "immediate command sequence\n");
			break;
		case 0x09:
			dev_warn(&device->cdev->dev,
				    "FORMAT 7 - Invalid tag-in for an "
				    "extended command sequence\n");
			break;
		case 0x0A:
			dev_warn(&device->cdev->dev,
				    "FORMAT 7 - 3990 microcode time out when "
				    "stopping selection\n");
			break;
		case 0x0B:
			dev_warn(&device->cdev->dev,
				    "FORMAT 7 - No response to selection "
				    "after a poll interruption\n");
			break;
		case 0x0C:
			dev_warn(&device->cdev->dev,
				    "FORMAT 7 - Permanent path error (DASD "
				    "controller not available)\n");
			break;
		case 0x0D:
			dev_warn(&device->cdev->dev,
				    "FORMAT 7 - DASD controller not available"
				    " on disconnected command chain\n");
			break;
		default:
			dev_warn(&device->cdev->dev,
				    "FORMAT 7 - Reserved\n");
		}
		break;

	case 0x80:  /* Format 8 - Additional Device Equipment Checks */
		switch (msg_no) {
		case 0x00:	/* No Message */
		case 0x01:
			dev_warn(&device->cdev->dev,
				    "FORMAT 8 - Error correction code "
				    "hardware fault\n");
			break;
		case 0x03:
			dev_warn(&device->cdev->dev,
				    "FORMAT 8 - Unexpected end operation "
				    "response code\n");
			break;
		case 0x04:
			dev_warn(&device->cdev->dev,
				    "FORMAT 8 - End operation with transfer "
				    "count not zero\n");
			break;
		case 0x05:
			dev_warn(&device->cdev->dev,
				    "FORMAT 8 - End operation with transfer "
				    "count zero\n");
			break;
		case 0x06:
			dev_warn(&device->cdev->dev,
				    "FORMAT 8 - DPS checks after a system "
				    "reset or selective reset\n");
			break;
		case 0x07:
			dev_warn(&device->cdev->dev,
				    "FORMAT 8 - DPS cannot be filled\n");
			break;
		case 0x08:
			dev_warn(&device->cdev->dev,
				    "FORMAT 8 - Short busy time-out during "
				    "device selection\n");
			break;
		case 0x09:
			dev_warn(&device->cdev->dev,
				    "FORMAT 8 - DASD controller failed to "
				    "set or reset the long busy latch\n");
			break;
		case 0x0A:
			dev_warn(&device->cdev->dev,
				    "FORMAT 8 - No interruption from device "
				    "during a command chain\n");
			break;
		default:
			dev_warn(&device->cdev->dev,
				    "FORMAT 8 - Reserved\n");
		}
		break;

	case 0x90:  /* Format 9 - Device Read, Write, and Seek Checks */
		switch (msg_no) {
		case 0x00:
			break;	/* No Message */
		case 0x06:
			dev_warn(&device->cdev->dev,
				    "FORMAT 9 - Device check-2 error\n");
			break;
		case 0x07:
			dev_warn(&device->cdev->dev,
				 "FORMAT 9 - Head address did not "
				 "compare\n");
			break;
		case 0x0A:
			dev_warn(&device->cdev->dev,
				    "FORMAT 9 - Track physical address did "
				    "not compare while oriented\n");
			break;
		case 0x0E:
			dev_warn(&device->cdev->dev,
				    "FORMAT 9 - Cylinder address did not "
				    "compare\n");
			break;
		default:
			dev_warn(&device->cdev->dev,
				    "FORMAT 9 - Reserved\n");
		}
		break;

	case 0xF0:		/* Format F - Cache Storage Checks */
		switch (msg_no) {
		case 0x00:
			dev_warn(&device->cdev->dev,
				    "FORMAT F - Operation Terminated\n");
			break;
		case 0x01:
			dev_warn(&device->cdev->dev,
				    "FORMAT F - Subsystem Processing Error\n");
			break;
		case 0x02:
			dev_warn(&device->cdev->dev,
				    "FORMAT F - Cache or nonvolatile storage "
				    "equipment failure\n");
			break;
		case 0x04:
			dev_warn(&device->cdev->dev,
				    "FORMAT F - Caching terminated\n");
			break;
		case 0x06:
			dev_warn(&device->cdev->dev,
				    "FORMAT F - Cache fast write access not "
				    "authorized\n");
			break;
		case 0x07:
			dev_warn(&device->cdev->dev,
				    "FORMAT F - Track format incorrect\n");
			break;
		case 0x09:
			dev_warn(&device->cdev->dev,
				    "FORMAT F - Caching reinitiated\n");
			break;
		case 0x0A:
			dev_warn(&device->cdev->dev,
				    "FORMAT F - Nonvolatile storage "
				    "terminated\n");
			break;
		case 0x0B:
			dev_warn(&device->cdev->dev,
				    "FORMAT F - Volume is suspended duplex\n");
			/* call extended error reporting (EER) */
			dasd_eer_write(device, erp->refers,
				       DASD_EER_PPRCSUSPEND);
			break;
		case 0x0C:
			dev_warn(&device->cdev->dev,
				    "FORMAT F - Subsystem status cannot be "
				    "determined\n");
			break;
		case 0x0D:
			dev_warn(&device->cdev->dev,
				    "FORMAT F - Caching status reset to "
				    "default\n");
			break;
		case 0x0E:
			dev_warn(&device->cdev->dev,
				    "FORMAT F - DASD Fast Write inhibited\n");
			break;
		default:
			dev_warn(&device->cdev->dev,
				    "FORMAT F - Reserved\n");
		}
		break;

	default:	/* unknown message format - should not happen
			   internal error 03 - unknown message format */
		snprintf(errorstring, ERRORLENGTH, "03 %x02", msg_format);
		dev_err(&device->cdev->dev,
			 "An error occurred in the DASD device driver, "
			 "reason=%s\n", errorstring);
		break;
	}			/* end switch message format */

}