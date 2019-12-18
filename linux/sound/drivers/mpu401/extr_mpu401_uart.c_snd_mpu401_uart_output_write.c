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
struct snd_mpu401 {int /*<<< orphan*/  substream_output; int /*<<< orphan*/  (* write ) (struct snd_mpu401*,unsigned char,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MPU401D (struct snd_mpu401*) ; 
 int /*<<< orphan*/  snd_mpu401_output_ready (struct snd_mpu401*) ; 
 int /*<<< orphan*/  snd_mpu401_uart_remove_timer (struct snd_mpu401*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_rawmidi_transmit_ack (int /*<<< orphan*/ ,int) ; 
 int snd_rawmidi_transmit_peek (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  stub1 (struct snd_mpu401*,unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_mpu401_uart_output_write(struct snd_mpu401 * mpu)
{
	unsigned char byte;
	int max = 256;

	do {
		if (snd_rawmidi_transmit_peek(mpu->substream_output,
					      &byte, 1) == 1) {
			/*
			 * Try twice because there is hardware that insists on
			 * setting the output busy bit after each write.
			 */
			if (!snd_mpu401_output_ready(mpu) &&
			    !snd_mpu401_output_ready(mpu))
				break;	/* Tx FIFO full - try again later */
			mpu->write(mpu, byte, MPU401D(mpu));
			snd_rawmidi_transmit_ack(mpu->substream_output, 1);
		} else {
			snd_mpu401_uart_remove_timer (mpu, 0);
			break;	/* no other data - leave the tx loop */
		}
	} while (--max > 0);
}