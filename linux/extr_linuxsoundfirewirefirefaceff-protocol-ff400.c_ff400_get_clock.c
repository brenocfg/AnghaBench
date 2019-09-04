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
struct snd_ff {int /*<<< orphan*/  unit; } ;
typedef  int /*<<< orphan*/  reg ;
typedef  enum snd_ff_clock_src { ____Placeholder_snd_ff_clock_src } snd_ff_clock_src ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  FF400_CLOCK_CONFIG ; 
 int SND_FF_CLOCK_SRC_ADAT ; 
 int SND_FF_CLOCK_SRC_INTERNAL ; 
 int SND_FF_CLOCK_SRC_LTC ; 
 int SND_FF_CLOCK_SRC_SPDIF ; 
 int SND_FF_CLOCK_SRC_WORD ; 
 int /*<<< orphan*/  TCODE_READ_QUADLET_REQUEST ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int snd_fw_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ff400_get_clock(struct snd_ff *ff, unsigned int *rate,
			   enum snd_ff_clock_src *src)
{
	__le32 reg;
	u32 data;
	int err;

	err = snd_fw_transaction(ff->unit, TCODE_READ_QUADLET_REQUEST,
				 FF400_CLOCK_CONFIG, &reg, sizeof(reg), 0);
	if (err < 0)
		return err;
	data = le32_to_cpu(reg);

	/* Calculate sampling rate. */
	switch ((data >> 1) & 0x03) {
	case 0x01:
		*rate = 32000;
		break;
	case 0x00:
		*rate = 44100;
		break;
	case 0x03:
		*rate = 48000;
		break;
	case 0x02:
	default:
		return -EIO;
	}

	if (data & 0x08)
		*rate *= 2;
	else if (data & 0x10)
		*rate *= 4;

	/* Calculate source of clock. */
	if (data & 0x01) {
		*src = SND_FF_CLOCK_SRC_INTERNAL;
	} else {
		/* TODO: 0x00, 0x01, 0x02, 0x06, 0x07? */
		switch ((data >> 10) & 0x07) {
		case 0x03:
			*src = SND_FF_CLOCK_SRC_SPDIF;
			break;
		case 0x04:
			*src = SND_FF_CLOCK_SRC_WORD;
			break;
		case 0x05:
			*src = SND_FF_CLOCK_SRC_LTC;
			break;
		case 0x00:
		default:
			*src = SND_FF_CLOCK_SRC_ADAT;
			break;
		}
	}

	return 0;
}