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
struct snd_aw2_saa7146 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACON1 ; 
 int /*<<< orphan*/  MC1 ; 
 unsigned int READREG (int /*<<< orphan*/ ) ; 
 int TR_E_A1_OUT ; 
 int TR_E_A2_OUT ; 
 int /*<<< orphan*/  WRITEREG (int,int /*<<< orphan*/ ) ; 
 int WS1_CTRL ; 
 int WS2_CTRL ; 

void snd_aw2_saa7146_pcm_trigger_stop_playback(struct snd_aw2_saa7146 *chip,
					       int stream_number)
{
	unsigned int acon1 = 0;
	acon1 = READREG(ACON1);
	if (stream_number == 0) {
		/* WS2_CTRL, WS2_SYNC: output TSL2, I2S */
		acon1 &= ~(3 * WS2_CTRL);
		WRITEREG(acon1, ACON1);

		WRITEREG((TR_E_A2_OUT << 16), MC1);
	} else if (stream_number == 1) {
		/* WS1_CTRL, WS1_SYNC: output TSL1, I2S */
		acon1 &= ~(3 * WS1_CTRL);
		WRITEREG(acon1, ACON1);

		WRITEREG((TR_E_A1_OUT << 16), MC1);
	}
}