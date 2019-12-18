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
struct hdsp {int control_register; int control2_register; scalar_t__ io_type; int /*<<< orphan*/ * mixer_matrix; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ H9632 ; 
 scalar_t__ H9652 ; 
 int HDSP_ADGainPlus4dBu ; 
 int HDSP_BIGENDIAN_MODE ; 
 int HDSP_ClockModeMaster ; 
 int HDSP_DAGainPlus4dBu ; 
 int HDSP_LineOut ; 
 unsigned int HDSP_MATRIX_MIXER_SIZE ; 
 int HDSP_PhoneGain0dB ; 
 int HDSP_SPDIFInputCoaxial ; 
 int /*<<< orphan*/  HDSP_control2Reg ; 
 int /*<<< orphan*/  HDSP_controlRegister ; 
 int /*<<< orphan*/  MINUS_INFINITY_GAIN ; 
 int /*<<< orphan*/  hdsp_compute_period_size (struct hdsp*) ; 
 int hdsp_encode_latency (int) ; 
 int /*<<< orphan*/  hdsp_reset_hw_pointer (struct hdsp*) ; 
 int /*<<< orphan*/  hdsp_set_rate (struct hdsp*,int,int) ; 
 int /*<<< orphan*/  hdsp_write (struct hdsp*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ hdsp_write_gain (struct hdsp*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hdsp_9652_enable_mixer (struct hdsp*) ; 

__attribute__((used)) static int snd_hdsp_set_defaults(struct hdsp *hdsp)
{
	unsigned int i;

	/* ASSUMPTION: hdsp->lock is either held, or
	   there is no need to hold it (e.g. during module
	   initialization).
	 */

	/* set defaults:

	   SPDIF Input via Coax
	   Master clock mode
	   maximum latency (7 => 2^7 = 8192 samples, 64Kbyte buffer,
	                    which implies 2 4096 sample, 32Kbyte periods).
           Enable line out.
	 */

	hdsp->control_register = HDSP_ClockModeMaster |
		                 HDSP_SPDIFInputCoaxial |
		                 hdsp_encode_latency(7) |
		                 HDSP_LineOut;


	hdsp_write(hdsp, HDSP_controlRegister, hdsp->control_register);

#ifdef SNDRV_BIG_ENDIAN
	hdsp->control2_register = HDSP_BIGENDIAN_MODE;
#else
	hdsp->control2_register = 0;
#endif
	if (hdsp->io_type == H9652)
	        snd_hdsp_9652_enable_mixer (hdsp);
	else
		hdsp_write (hdsp, HDSP_control2Reg, hdsp->control2_register);

	hdsp_reset_hw_pointer(hdsp);
	hdsp_compute_period_size(hdsp);

	/* silence everything */

	for (i = 0; i < HDSP_MATRIX_MIXER_SIZE; ++i)
		hdsp->mixer_matrix[i] = MINUS_INFINITY_GAIN;

	for (i = 0; i < ((hdsp->io_type == H9652 || hdsp->io_type == H9632) ? 1352 : HDSP_MATRIX_MIXER_SIZE); ++i) {
		if (hdsp_write_gain (hdsp, i, MINUS_INFINITY_GAIN))
			return -EIO;
	}

	/* H9632 specific defaults */
	if (hdsp->io_type == H9632) {
		hdsp->control_register |= (HDSP_DAGainPlus4dBu | HDSP_ADGainPlus4dBu | HDSP_PhoneGain0dB);
		hdsp_write(hdsp, HDSP_controlRegister, hdsp->control_register);
	}

	/* set a default rate so that the channel map is set up.
	 */

	hdsp_set_rate(hdsp, 48000, 1);

	return 0;
}