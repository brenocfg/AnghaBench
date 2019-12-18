#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct snd_rawmidi* rmidi; TYPE_3__* card; scalar_t__ mmio; } ;
typedef  TYPE_1__ vortex_t ;
struct snd_rawmidi {int /*<<< orphan*/  name; struct snd_mpu401* private_data; } ;
struct snd_mpu401 {unsigned long cport; } ;
struct TYPE_5__ {int number; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 char* CARD_NAME_SHORT ; 
 unsigned long CTRL_MIDI_EN ; 
 unsigned long CTRL_MIDI_PORT ; 
 int ENODEV ; 
 unsigned long IRQ_MIDI ; 
 int MIDI_CLOCK_DIV ; 
 int MPU401_ACK ; 
 int /*<<< orphan*/  MPU401_HW_AUREAL ; 
 int /*<<< orphan*/  MPU401_HW_MPU401 ; 
 int MPU401_INFO_INTEGRATED ; 
 int MPU401_INFO_IRQ_HOOK ; 
 int MPU401_INFO_MMIO ; 
 unsigned long MPU401_RESET ; 
 scalar_t__ VORTEX_CTRL ; 
 scalar_t__ VORTEX_CTRL2 ; 
 scalar_t__ VORTEX_IRQ_CTRL ; 
 scalar_t__ VORTEX_MIDI_CMD ; 
 scalar_t__ VORTEX_MIDI_DATA ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned long hwread (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  hwwrite (scalar_t__,scalar_t__,unsigned long) ; 
 int snd_mpu401_uart_new (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int,int,struct snd_rawmidi**) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int) ; 

__attribute__((used)) static int snd_vortex_midi(vortex_t *vortex)
{
	struct snd_rawmidi *rmidi;
	int temp, mode;
	struct snd_mpu401 *mpu;
	unsigned long port;

#ifdef VORTEX_MPU401_LEGACY
	/* EnableHardCodedMPU401Port() */
	/* Enable Legacy MIDI Interface port. */
	port = (0x03 << 5);	/* FIXME: static address. 0x330 */
	temp =
	    (hwread(vortex->mmio, VORTEX_CTRL) & ~CTRL_MIDI_PORT) |
	    CTRL_MIDI_EN | port;
	hwwrite(vortex->mmio, VORTEX_CTRL, temp);
#else
	/* Disable Legacy MIDI Interface port. */
	temp =
	    (hwread(vortex->mmio, VORTEX_CTRL) & ~CTRL_MIDI_PORT) &
	    ~CTRL_MIDI_EN;
	hwwrite(vortex->mmio, VORTEX_CTRL, temp);
#endif
	/* Mpu401UartInit() */
	mode = 1;
	temp = hwread(vortex->mmio, VORTEX_CTRL2) & 0xffff00cf;
	temp |= (MIDI_CLOCK_DIV << 8) | ((mode >> 24) & 0xff) << 4;
	hwwrite(vortex->mmio, VORTEX_CTRL2, temp);
	hwwrite(vortex->mmio, VORTEX_MIDI_CMD, MPU401_RESET);

	/* Check if anything is OK. */
	temp = hwread(vortex->mmio, VORTEX_MIDI_DATA);
	if (temp != MPU401_ACK /*0xfe */ ) {
		dev_err(vortex->card->dev, "midi port doesn't acknowledge!\n");
		return -ENODEV;
	}
	/* Enable MPU401 interrupts. */
	hwwrite(vortex->mmio, VORTEX_IRQ_CTRL,
		hwread(vortex->mmio, VORTEX_IRQ_CTRL) | IRQ_MIDI);

	/* Create MPU401 instance. */
#ifdef VORTEX_MPU401_LEGACY
	if ((temp =
	     snd_mpu401_uart_new(vortex->card, 0, MPU401_HW_MPU401, 0x330,
				 MPU401_INFO_IRQ_HOOK, -1, &rmidi)) != 0) {
		hwwrite(vortex->mmio, VORTEX_CTRL,
			(hwread(vortex->mmio, VORTEX_CTRL) &
			 ~CTRL_MIDI_PORT) & ~CTRL_MIDI_EN);
		return temp;
	}
#else
	port = (unsigned long)(vortex->mmio + VORTEX_MIDI_DATA);
	if ((temp =
	     snd_mpu401_uart_new(vortex->card, 0, MPU401_HW_AUREAL, port,
				 MPU401_INFO_INTEGRATED | MPU401_INFO_MMIO |
				 MPU401_INFO_IRQ_HOOK, -1, &rmidi)) != 0) {
		hwwrite(vortex->mmio, VORTEX_CTRL,
			(hwread(vortex->mmio, VORTEX_CTRL) &
			 ~CTRL_MIDI_PORT) & ~CTRL_MIDI_EN);
		return temp;
	}
	mpu = rmidi->private_data;
	mpu->cport = (unsigned long)(vortex->mmio + VORTEX_MIDI_CMD);
#endif
	/* Overwrite MIDI name */
	snprintf(rmidi->name, sizeof(rmidi->name), "%s MIDI %d", CARD_NAME_SHORT , vortex->card->number);

	vortex->rmidi = rmidi;
	return 0;
}