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
 int /*<<< orphan*/  MC1 ; 
 int TR_E_A1_IN ; 
 int /*<<< orphan*/  WRITEREG (int,int /*<<< orphan*/ ) ; 

void snd_aw2_saa7146_pcm_trigger_start_capture(struct snd_aw2_saa7146 *chip,
					       int stream_number)
{
	/* In aw8 driver, dma transfert is always active. It is
	   started and stopped in a larger "space" */
	if (stream_number == 0)
		WRITEREG((TR_E_A1_IN << 16) | TR_E_A1_IN, MC1);
}