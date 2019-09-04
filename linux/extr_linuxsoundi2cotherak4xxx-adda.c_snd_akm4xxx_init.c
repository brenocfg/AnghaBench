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
struct snd_akm4xxx {int type; int num_chips; int num_dacs; char* name; int total_regs; int /*<<< orphan*/  volumes; int /*<<< orphan*/  images; } ;

/* Variables and functions */
#define  SND_AK4355 135 
#define  SND_AK4358 134 
#define  SND_AK4381 133 
#define  SND_AK4524 132 
#define  SND_AK4528 131 
#define  SND_AK4529 130 
#define  SND_AK4620 129 
#define  SND_AK5365 128 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_BUG () ; 
 int /*<<< orphan*/  snd_akm4xxx_write (struct snd_akm4xxx*,int,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  udelay (int) ; 

void snd_akm4xxx_init(struct snd_akm4xxx *ak)
{
	static const unsigned char inits_ak4524[] = {
		0x00, 0x07, /* 0: all power up */
		0x01, 0x00, /* 1: ADC/DAC reset */
		0x02, 0x60, /* 2: 24bit I2S */
		0x03, 0x19, /* 3: deemphasis off */
		0x01, 0x03, /* 1: ADC/DAC enable */
		0x04, 0x00, /* 4: ADC left muted */
		0x05, 0x00, /* 5: ADC right muted */
		0x06, 0x00, /* 6: DAC left muted */
		0x07, 0x00, /* 7: DAC right muted */
		0xff, 0xff
	};
	static const unsigned char inits_ak4528[] = {
		0x00, 0x07, /* 0: all power up */
		0x01, 0x00, /* 1: ADC/DAC reset */
		0x02, 0x60, /* 2: 24bit I2S */
		0x03, 0x0d, /* 3: deemphasis off, turn LR highpass filters on */
		0x01, 0x03, /* 1: ADC/DAC enable */
		0x04, 0x00, /* 4: ADC left muted */
		0x05, 0x00, /* 5: ADC right muted */
		0xff, 0xff
	};
	static const unsigned char inits_ak4529[] = {
		0x09, 0x01, /* 9: ATS=0, RSTN=1 */
		0x0a, 0x3f, /* A: all power up, no zero/overflow detection */
		0x00, 0x0c, /* 0: TDM=0, 24bit I2S, SMUTE=0 */
		0x01, 0x00, /* 1: ACKS=0, ADC, loop off */
		0x02, 0xff, /* 2: LOUT1 muted */
		0x03, 0xff, /* 3: ROUT1 muted */
		0x04, 0xff, /* 4: LOUT2 muted */
		0x05, 0xff, /* 5: ROUT2 muted */
		0x06, 0xff, /* 6: LOUT3 muted */
		0x07, 0xff, /* 7: ROUT3 muted */
		0x0b, 0xff, /* B: LOUT4 muted */
		0x0c, 0xff, /* C: ROUT4 muted */
		0x08, 0x55, /* 8: deemphasis all off */
		0xff, 0xff
	};
	static const unsigned char inits_ak4355[] = {
		0x01, 0x02, /* 1: reset and soft-mute */
		0x00, 0x06, /* 0: mode3(i2s), disable auto-clock detect,
			     * disable DZF, sharp roll-off, RSTN#=0 */
		0x02, 0x0e, /* 2: DA's power up, normal speed, RSTN#=0 */
		// 0x02, 0x2e, /* quad speed */
		0x03, 0x01, /* 3: de-emphasis off */
		0x04, 0x00, /* 4: LOUT1 volume muted */
		0x05, 0x00, /* 5: ROUT1 volume muted */
		0x06, 0x00, /* 6: LOUT2 volume muted */
		0x07, 0x00, /* 7: ROUT2 volume muted */
		0x08, 0x00, /* 8: LOUT3 volume muted */
		0x09, 0x00, /* 9: ROUT3 volume muted */
		0x0a, 0x00, /* a: DATT speed=0, ignore DZF */
		0x01, 0x01, /* 1: un-reset, unmute */
		0xff, 0xff
	};
	static const unsigned char inits_ak4358[] = {
		0x01, 0x02, /* 1: reset and soft-mute */
		0x00, 0x06, /* 0: mode3(i2s), disable auto-clock detect,
			     * disable DZF, sharp roll-off, RSTN#=0 */
		0x02, 0x4e, /* 2: DA's power up, normal speed, RSTN#=0 */
		/* 0x02, 0x6e,*/ /* quad speed */
		0x03, 0x01, /* 3: de-emphasis off */
		0x04, 0x00, /* 4: LOUT1 volume muted */
		0x05, 0x00, /* 5: ROUT1 volume muted */
		0x06, 0x00, /* 6: LOUT2 volume muted */
		0x07, 0x00, /* 7: ROUT2 volume muted */
		0x08, 0x00, /* 8: LOUT3 volume muted */
		0x09, 0x00, /* 9: ROUT3 volume muted */
		0x0b, 0x00, /* b: LOUT4 volume muted */
		0x0c, 0x00, /* c: ROUT4 volume muted */
		0x0a, 0x00, /* a: DATT speed=0, ignore DZF */
		0x01, 0x01, /* 1: un-reset, unmute */
		0xff, 0xff
	};
	static const unsigned char inits_ak4381[] = {
		0x00, 0x0c, /* 0: mode3(i2s), disable auto-clock detect */
		0x01, 0x02, /* 1: de-emphasis off, normal speed,
			     * sharp roll-off, DZF off */
		// 0x01, 0x12, /* quad speed */
		0x02, 0x00, /* 2: DZF disabled */
		0x03, 0x00, /* 3: LATT 0 */
		0x04, 0x00, /* 4: RATT 0 */
		0x00, 0x0f, /* 0: power-up, un-reset */
		0xff, 0xff
	};
	static const unsigned char inits_ak4620[] = {
		0x00, 0x07, /* 0: normal */
		0x01, 0x00, /* 0: reset */
		0x01, 0x02, /* 1: RSTAD */
		0x01, 0x03, /* 1: RSTDA */
		0x01, 0x0f, /* 1: normal */
		0x02, 0x60, /* 2: 24bit I2S */
		0x03, 0x01, /* 3: deemphasis off */
		0x04, 0x00, /* 4: LIN muted */
		0x05, 0x00, /* 5: RIN muted */
		0x06, 0x00, /* 6: LOUT muted */
		0x07, 0x00, /* 7: ROUT muted */
		0xff, 0xff
	};

	int chip;
	const unsigned char *ptr, *inits;
	unsigned char reg, data;

	memset(ak->images, 0, sizeof(ak->images));
	memset(ak->volumes, 0, sizeof(ak->volumes));

	switch (ak->type) {
	case SND_AK4524:
		inits = inits_ak4524;
		ak->num_chips = ak->num_dacs / 2;
		ak->name = "ak4524";
		ak->total_regs = 0x08;
		break;
	case SND_AK4528:
		inits = inits_ak4528;
		ak->num_chips = ak->num_dacs / 2;
		ak->name = "ak4528";
		ak->total_regs = 0x06;
		break;
	case SND_AK4529:
		inits = inits_ak4529;
		ak->num_chips = 1;
		ak->name = "ak4529";
		ak->total_regs = 0x0d;
		break;
	case SND_AK4355:
		inits = inits_ak4355;
		ak->num_chips = 1;
		ak->name = "ak4355";
		ak->total_regs = 0x0b;
		break;
	case SND_AK4358:
		inits = inits_ak4358;
		ak->num_chips = 1;
		ak->name = "ak4358";
		ak->total_regs = 0x10;
		break;
	case SND_AK4381:
		inits = inits_ak4381;
		ak->num_chips = ak->num_dacs / 2;
		ak->name = "ak4381";
		ak->total_regs = 0x05;
		break;
	case SND_AK5365:
		/* FIXME: any init sequence? */
		ak->num_chips = 1;
		ak->name = "ak5365";
		ak->total_regs = 0x08;
		return;
	case SND_AK4620:
		inits = inits_ak4620;
		ak->num_chips = ak->num_dacs / 2;
		ak->name = "ak4620";
		ak->total_regs = 0x08;
		break;
	default:
		snd_BUG();
		return;
	}

	for (chip = 0; chip < ak->num_chips; chip++) {
		ptr = inits;
		while (*ptr != 0xff) {
			reg = *ptr++;
			data = *ptr++;
			snd_akm4xxx_write(ak, chip, reg, data);
			udelay(10);
		}
	}
}