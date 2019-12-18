#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct atiixp_modem {int codec_not_ready_bits; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ALL_CODEC_NOT_READY ; 
 int /*<<< orphan*/  CODEC_CHECK_BITS ; 
 int ENXIO ; 
 int /*<<< orphan*/  IER ; 
 int /*<<< orphan*/  atiixp_write (struct atiixp_modem*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int snd_atiixp_codec_detect(struct atiixp_modem *chip)
{
	int timeout;

	chip->codec_not_ready_bits = 0;
	atiixp_write(chip, IER, CODEC_CHECK_BITS);
	/* wait for the interrupts */
	timeout = 50;
	while (timeout-- > 0) {
		msleep(1);
		if (chip->codec_not_ready_bits)
			break;
	}
	atiixp_write(chip, IER, 0); /* disable irqs */

	if ((chip->codec_not_ready_bits & ALL_CODEC_NOT_READY) == ALL_CODEC_NOT_READY) {
		dev_err(chip->card->dev, "no codec detected!\n");
		return -ENXIO;
	}
	return 0;
}