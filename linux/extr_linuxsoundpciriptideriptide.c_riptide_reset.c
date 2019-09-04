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
union cmdret {int /*<<< orphan*/ * retlongs; } ;
typedef  int u32 ;
struct snd_riptide {int dummy; } ;
struct cmdif {int cmdtimemin; int is_reset; int /*<<< orphan*/  hwport; scalar_t__ errcnt; scalar_t__ cmdtimemax; scalar_t__ cmdtime; scalar_t__ cmdcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_RESET ; 
 int /*<<< orphan*/  ARM2LBUS_FIFO0 ; 
 int /*<<< orphan*/  ARM2LBUS_FIFO13 ; 
 union cmdret CMDRET_ZERO ; 
 int /*<<< orphan*/  DIGITAL_MIXER_OUT0 ; 
 int EINVAL ; 
 int /*<<< orphan*/  FM_CMD ; 
 int /*<<< orphan*/  FM_INTDEC ; 
 int /*<<< orphan*/  FM_MERGER ; 
 int FM_MIXER ; 
 int /*<<< orphan*/  FM_SPLITTER ; 
 int /*<<< orphan*/  I2S_CMD0 ; 
 int /*<<< orphan*/  I2S_INTDEC ; 
 int /*<<< orphan*/  I2S_MERGER ; 
 int I2S_MIXER ; 
 scalar_t__ I2S_RATE ; 
 int /*<<< orphan*/  I2S_SPLITTER ; 
 int /*<<< orphan*/  MODEM_CMD ; 
 int /*<<< orphan*/  MODEM_INTDEC ; 
 int /*<<< orphan*/  MODEM_MERGER ; 
 int MODEM_MIXER ; 
 int /*<<< orphan*/  MODEM_SPLITTER ; 
 int /*<<< orphan*/  OPL3_SAMPLE ; 
 int RESET_TRIES ; 
 int /*<<< orphan*/  SEND_ALST (struct cmdif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEND_DLST (struct cmdif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEND_KDMA (struct cmdif*) ; 
 int /*<<< orphan*/  SEND_LSEL (struct cmdif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SEND_PLST (struct cmdif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEND_RACR (struct cmdif*,int /*<<< orphan*/ ,union cmdret*) ; 
 int /*<<< orphan*/  SEND_SACR (struct cmdif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEND_SI2S (struct cmdif*,int) ; 
 int /*<<< orphan*/  SEND_SLST (struct cmdif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEND_SSRC (struct cmdif*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  SET_AIACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_AIE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloclbuspath (struct cmdif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lbus_play_i2s ; 
 int /*<<< orphan*/  lbus_play_modem ; 
 int /*<<< orphan*/  lbus_play_opl3 ; 
 int /*<<< orphan*/  lbus_play_out ; 
 int /*<<< orphan*/  lbus_play_outhp ; 
 int /*<<< orphan*/  setmixer (struct cmdif*,int,int,int) ; 
 int /*<<< orphan*/  snd_printdd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int try_to_load_firmware (struct cmdif*,struct snd_riptide*) ; 
 int /*<<< orphan*/  writearm (struct cmdif*,int,int,int) ; 

__attribute__((used)) static int riptide_reset(struct cmdif *cif, struct snd_riptide *chip)
{
	union cmdret rptr = CMDRET_ZERO;
	int err, tries;

	if (!cif)
		return -EINVAL;

	cif->cmdcnt = 0;
	cif->cmdtime = 0;
	cif->cmdtimemax = 0;
	cif->cmdtimemin = 0xffffffff;
	cif->errcnt = 0;
	cif->is_reset = 0;

	tries = RESET_TRIES;
	do {
		err = try_to_load_firmware(cif, chip);
		if (err < 0)
			return err;
	} while (!err && --tries);

	SEND_SACR(cif, 0, AC97_RESET);
	SEND_RACR(cif, AC97_RESET, &rptr);
	snd_printdd("AC97: 0x%x 0x%x\n", rptr.retlongs[0], rptr.retlongs[1]);

	SEND_PLST(cif, 0);
	SEND_SLST(cif, 0);
	SEND_DLST(cif, 0);
	SEND_ALST(cif, 0);
	SEND_KDMA(cif);

	writearm(cif, 0x301F8, 1, 1);
	writearm(cif, 0x301F4, 1, 1);

	SEND_LSEL(cif, MODEM_CMD, 0, 0, MODEM_INTDEC, MODEM_MERGER,
		  MODEM_SPLITTER, MODEM_MIXER);
	setmixer(cif, MODEM_MIXER, 0x7fff, 0x7fff);
	alloclbuspath(cif, ARM2LBUS_FIFO13, lbus_play_modem, NULL, NULL);

	SEND_LSEL(cif, FM_CMD, 0, 0, FM_INTDEC, FM_MERGER, FM_SPLITTER,
		  FM_MIXER);
	setmixer(cif, FM_MIXER, 0x7fff, 0x7fff);
	writearm(cif, 0x30648 + FM_MIXER * 4, 0x01, 0x00000005);
	writearm(cif, 0x301A8, 0x02, 0x00000002);
	writearm(cif, 0x30264, 0x08, 0xffffffff);
	alloclbuspath(cif, OPL3_SAMPLE, lbus_play_opl3, NULL, NULL);

	SEND_SSRC(cif, I2S_INTDEC, 48000,
		  ((u32) I2S_RATE * 65536) / 48000,
		  ((u32) I2S_RATE * 65536) % 48000);
	SEND_LSEL(cif, I2S_CMD0, 0, 0, I2S_INTDEC, I2S_MERGER, I2S_SPLITTER,
		  I2S_MIXER);
	SEND_SI2S(cif, 1);
	alloclbuspath(cif, ARM2LBUS_FIFO0, lbus_play_i2s, NULL, NULL);
	alloclbuspath(cif, DIGITAL_MIXER_OUT0, lbus_play_out, NULL, NULL);
	alloclbuspath(cif, DIGITAL_MIXER_OUT0, lbus_play_outhp, NULL, NULL);

	SET_AIACK(cif->hwport);
	SET_AIE(cif->hwport);
	SET_AIACK(cif->hwport);
	cif->is_reset = 1;

	return 0;
}