#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mmio; TYPE_1__* card; } ;
typedef  TYPE_2__ vortex_t ;
struct snd_ac97 {unsigned short num; scalar_t__ private_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  POLL_COUNT ; 
 unsigned short VORTEX_CODEC_ADDMASK ; 
 unsigned short VORTEX_CODEC_ADDSHIFT ; 
 int /*<<< orphan*/  VORTEX_CODEC_CTRL ; 
 unsigned short VORTEX_CODEC_DATMASK ; 
 unsigned short VORTEX_CODEC_DATSHIFT ; 
 unsigned short VORTEX_CODEC_ID_SHIFT ; 
 int /*<<< orphan*/  VORTEX_CODEC_IO ; 
 unsigned short VORTEX_CODEC_WRITE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int hwread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
vortex_codec_write(struct snd_ac97 * codec, unsigned short addr, unsigned short data)
{

	vortex_t *card = (vortex_t *) codec->private_data;
	unsigned int lifeboat = 0;

	/* wait for transactions to clear */
	while (!(hwread(card->mmio, VORTEX_CODEC_CTRL) & 0x100)) {
		udelay(100);
		if (lifeboat++ > POLL_COUNT) {
			dev_err(card->card->dev, "ac97 codec stuck busy\n");
			return;
		}
	}
	/* write register */
	hwwrite(card->mmio, VORTEX_CODEC_IO,
		((addr << VORTEX_CODEC_ADDSHIFT) & VORTEX_CODEC_ADDMASK) |
		((data << VORTEX_CODEC_DATSHIFT) & VORTEX_CODEC_DATMASK) |
		VORTEX_CODEC_WRITE |
		(codec->num << VORTEX_CODEC_ID_SHIFT) );

	/* Flush Caches. */
	hwread(card->mmio, VORTEX_CODEC_IO);
}