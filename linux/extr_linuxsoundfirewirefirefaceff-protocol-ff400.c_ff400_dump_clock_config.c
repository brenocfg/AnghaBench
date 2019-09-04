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
 int /*<<< orphan*/  FF400_CLOCK_CONFIG ; 
 int /*<<< orphan*/  TCODE_READ_BLOCK_REQUEST ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int snd_fw_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 

__attribute__((used)) static void ff400_dump_clock_config(struct snd_ff *ff,
				    struct snd_info_buffer *buffer)
{
	__le32 reg;
	u32 data;
	unsigned int rate;
	const char *src;
	int err;

	err = snd_fw_transaction(ff->unit, TCODE_READ_BLOCK_REQUEST,
				 FF400_CLOCK_CONFIG, &reg, sizeof(reg), 0);
	if (err < 0)
		return;

	data = le32_to_cpu(reg);

	snd_iprintf(buffer, "Output S/PDIF format: %s (Emphasis: %s)\n",
		    (data & 0x20) ? "Professional" : "Consumer",
		    (data & 0x40) ? "on" : "off");

	snd_iprintf(buffer, "Optical output interface format: %s\n",
		    ((data >> 8) & 0x01) ? "S/PDIF" : "ADAT");

	snd_iprintf(buffer, "Word output single speed: %s\n",
		    ((data >> 8) & 0x20) ? "on" : "off");

	snd_iprintf(buffer, "S/PDIF input interface: %s\n",
		    ((data >> 8) & 0x02) ? "Optical" : "Coaxial");

	switch ((data >> 1) & 0x03) {
	case 0x01:
		rate = 32000;
		break;
	case 0x00:
		rate = 44100;
		break;
	case 0x03:
		rate = 48000;
		break;
	case 0x02:
	default:
		return;
	}

	if (data & 0x08)
		rate *= 2;
	else if (data & 0x10)
		rate *= 4;

	snd_iprintf(buffer, "Sampling rate: %d\n", rate);

	if (data & 0x01) {
		src = "Internal";
	} else {
		switch ((data >> 10) & 0x07) {
		case 0x00:
			src = "ADAT";
			break;
		case 0x03:
			src = "S/PDIF";
			break;
		case 0x04:
			src = "Word";
			break;
		case 0x05:
			src = "LTC";
			break;
		default:
			return;
		}
	}

	snd_iprintf(buffer, "Sync to clock source: %s\n", src);
}