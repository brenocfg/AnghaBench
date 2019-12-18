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
struct hdspm {int settings_register; int io_type; int control_register; int control2_register; } ;

/* Variables and functions */
#define  AES32 132 
#define  AIO 131 
 int HDSPM_BIGENDIAN_MODE ; 
 int HDSPM_ClockModeMaster ; 
 int HDSPM_LineOut ; 
 int HDSPM_Professional ; 
 int HDSPM_SyncRef0 ; 
 int /*<<< orphan*/  HDSPM_WR_SETTINGS ; 
 int /*<<< orphan*/  HDSPM_control2Reg ; 
 int /*<<< orphan*/  HDSPM_controlRegister ; 
#define  MADI 130 
#define  MADIface 129 
#define  RayDAT 128 
 int UNITY_GAIN ; 
 int /*<<< orphan*/  all_in_all_mixer (struct hdspm*,int) ; 
 int /*<<< orphan*/  hdspm_compute_period_size (struct hdspm*) ; 
 int hdspm_encode_latency (int) ; 
 scalar_t__ hdspm_is_raydat_or_aio (struct hdspm*) ; 
 int /*<<< orphan*/  hdspm_set_rate (struct hdspm*,int,int) ; 
 int /*<<< orphan*/  hdspm_write (struct hdspm*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int snd_hdspm_set_defaults(struct hdspm * hdspm)
{
	/* ASSUMPTION: hdspm->lock is either held, or there is no need to
	   hold it (e.g. during module initialization).
	   */

	/* set defaults:       */

	hdspm->settings_register = 0;

	switch (hdspm->io_type) {
	case MADI:
	case MADIface:
		hdspm->control_register =
			0x2 + 0x8 + 0x10 + 0x80 + 0x400 + 0x4000 + 0x1000000;
		break;

	case RayDAT:
	case AIO:
		hdspm->settings_register = 0x1 + 0x1000;
		/* Magic values are: LAT_0, LAT_2, Master, freq1, tx64ch, inp_0,
		 * line_out */
		hdspm->control_register =
			0x2 + 0x8 + 0x10 + 0x80 + 0x400 + 0x4000 + 0x1000000;
		break;

	case AES32:
		hdspm->control_register =
			HDSPM_ClockModeMaster |	/* Master Clock Mode on */
			hdspm_encode_latency(7) | /* latency max=8192samples */
			HDSPM_SyncRef0 |	/* AES1 is syncclock */
			HDSPM_LineOut |	/* Analog output in */
			HDSPM_Professional;  /* Professional mode */
		break;
	}

	hdspm_write(hdspm, HDSPM_controlRegister, hdspm->control_register);

	if (AES32 == hdspm->io_type) {
		/* No control2 register for AES32 */
#ifdef SNDRV_BIG_ENDIAN
		hdspm->control2_register = HDSPM_BIGENDIAN_MODE;
#else
		hdspm->control2_register = 0;
#endif

		hdspm_write(hdspm, HDSPM_control2Reg, hdspm->control2_register);
	}
	hdspm_compute_period_size(hdspm);

	/* silence everything */

	all_in_all_mixer(hdspm, 0 * UNITY_GAIN);

	if (hdspm_is_raydat_or_aio(hdspm))
		hdspm_write(hdspm, HDSPM_WR_SETTINGS, hdspm->settings_register);

	/* set a default rate so that the channel map is set up. */
	hdspm_set_rate(hdspm, 48000, 1);

	return 0;
}