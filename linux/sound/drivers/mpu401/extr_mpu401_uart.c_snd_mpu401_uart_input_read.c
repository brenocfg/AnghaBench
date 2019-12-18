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
struct snd_mpu401 {unsigned char (* read ) (struct snd_mpu401*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  substream_input; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPU401D (struct snd_mpu401*) ; 
 int /*<<< orphan*/  MPU401_MODE_BIT_INPUT_TRIGGER ; 
 int /*<<< orphan*/  snd_mpu401_input_avail (struct snd_mpu401*) ; 
 int /*<<< orphan*/  snd_rawmidi_receive (int /*<<< orphan*/ ,unsigned char*,int) ; 
 unsigned char stub1 (struct snd_mpu401*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_mpu401_uart_input_read(struct snd_mpu401 * mpu)
{
	int max = 128;
	unsigned char byte;

	while (max-- > 0) {
		if (! snd_mpu401_input_avail(mpu))
			break; /* input not available */
		byte = mpu->read(mpu, MPU401D(mpu));
		if (test_bit(MPU401_MODE_BIT_INPUT_TRIGGER, &mpu->mode))
			snd_rawmidi_receive(mpu->substream_input, &byte, 1);
	}
}