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
typedef  int u32 ;
struct snd_info_buffer {int dummy; } ;
struct snd_ff {int /*<<< orphan*/  unit; } ;
typedef  int /*<<< orphan*/  reg ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  FF400_SYNC_STATUS ; 
 int /*<<< orphan*/  TCODE_READ_QUADLET_REQUEST ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int snd_fw_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 

__attribute__((used)) static void ff400_dump_sync_status(struct snd_ff *ff,
				   struct snd_info_buffer *buffer)
{
	__le32 reg;
	u32 data;
	int err;

	err = snd_fw_transaction(ff->unit, TCODE_READ_QUADLET_REQUEST,
				 FF400_SYNC_STATUS, &reg, sizeof(reg), 0);
	if (err < 0)
		return;

	data = le32_to_cpu(reg);

	snd_iprintf(buffer, "External source detection:\n");

	snd_iprintf(buffer, "Word Clock:");
	if ((data >> 24) & 0x20) {
		if ((data >> 24) & 0x40)
			snd_iprintf(buffer, "sync\n");
		else
			snd_iprintf(buffer, "lock\n");
	} else {
		snd_iprintf(buffer, "none\n");
	}

	snd_iprintf(buffer, "S/PDIF:");
	if ((data >> 16) & 0x10) {
		if ((data >> 16) & 0x04)
			snd_iprintf(buffer, "sync\n");
		else
			snd_iprintf(buffer, "lock\n");
	} else {
		snd_iprintf(buffer, "none\n");
	}

	snd_iprintf(buffer, "ADAT:");
	if ((data >> 8) & 0x04) {
		if ((data >> 8) & 0x10)
			snd_iprintf(buffer, "sync\n");
		else
			snd_iprintf(buffer, "lock\n");
	} else {
		snd_iprintf(buffer, "none\n");
	}

	snd_iprintf(buffer, "\nUsed external source:\n");

	if (((data >> 22) & 0x07) == 0x07) {
		snd_iprintf(buffer, "None\n");
	} else {
		switch ((data >> 22) & 0x07) {
		case 0x00:
			snd_iprintf(buffer, "ADAT:");
			break;
		case 0x03:
			snd_iprintf(buffer, "S/PDIF:");
			break;
		case 0x04:
			snd_iprintf(buffer, "Word:");
			break;
		case 0x07:
			snd_iprintf(buffer, "Nothing:");
			break;
		case 0x01:
		case 0x02:
		case 0x05:
		case 0x06:
		default:
			snd_iprintf(buffer, "unknown:");
			break;
		}

		if ((data >> 25) & 0x07) {
			switch ((data >> 25) & 0x07) {
			case 0x01:
				snd_iprintf(buffer, "32000\n");
				break;
			case 0x02:
				snd_iprintf(buffer, "44100\n");
				break;
			case 0x03:
				snd_iprintf(buffer, "48000\n");
				break;
			case 0x04:
				snd_iprintf(buffer, "64000\n");
				break;
			case 0x05:
				snd_iprintf(buffer, "88200\n");
				break;
			case 0x06:
				snd_iprintf(buffer, "96000\n");
				break;
			case 0x07:
				snd_iprintf(buffer, "128000\n");
				break;
			case 0x08:
				snd_iprintf(buffer, "176400\n");
				break;
			case 0x09:
				snd_iprintf(buffer, "192000\n");
				break;
			case 0x00:
				snd_iprintf(buffer, "unknown\n");
				break;
			}
		}
	}

	snd_iprintf(buffer, "Multiplied:");
	snd_iprintf(buffer, "%d\n", (data & 0x3ff) * 250);
}