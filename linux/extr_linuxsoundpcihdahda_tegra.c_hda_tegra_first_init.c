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
struct snd_card {char* driver; char* shortname; int /*<<< orphan*/  longname; int /*<<< orphan*/  dev; } ;
struct platform_device {int dummy; } ;
struct hdac_bus {int irq; int /*<<< orphan*/  addr; int /*<<< orphan*/  codec_mask; } ;
struct azx {unsigned short capture_streams; unsigned short playback_streams; unsigned short playback_index_offset; unsigned short num_streams; scalar_t__ capture_index_offset; struct snd_card* card; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GCAP ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 unsigned short NUM_CAPTURE_SD ; 
 unsigned short NUM_PLAYBACK_SD ; 
 int azx_alloc_stream_pages (struct azx*) ; 
 struct hdac_bus* azx_bus (struct azx*) ; 
 int /*<<< orphan*/  azx_init_chip (struct azx*,int) ; 
 int azx_init_streams (struct azx*) ; 
 int /*<<< orphan*/  azx_interrupt ; 
 unsigned short azx_readw (struct azx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned short) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int devm_request_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct azx*) ; 
 int hda_tegra_init_chip (struct azx*,struct platform_device*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  synchronize_irq (int) ; 

__attribute__((used)) static int hda_tegra_first_init(struct azx *chip, struct platform_device *pdev)
{
	struct hdac_bus *bus = azx_bus(chip);
	struct snd_card *card = chip->card;
	int err;
	unsigned short gcap;
	int irq_id = platform_get_irq(pdev, 0);

	err = hda_tegra_init_chip(chip, pdev);
	if (err)
		return err;

	err = devm_request_irq(chip->card->dev, irq_id, azx_interrupt,
			     IRQF_SHARED, KBUILD_MODNAME, chip);
	if (err) {
		dev_err(chip->card->dev,
			"unable to request IRQ %d, disabling device\n",
			irq_id);
		return err;
	}
	bus->irq = irq_id;

	synchronize_irq(bus->irq);

	gcap = azx_readw(chip, GCAP);
	dev_dbg(card->dev, "chipset global capabilities = 0x%x\n", gcap);

	/* read number of streams from GCAP register instead of using
	 * hardcoded value
	 */
	chip->capture_streams = (gcap >> 8) & 0x0f;
	chip->playback_streams = (gcap >> 12) & 0x0f;
	if (!chip->playback_streams && !chip->capture_streams) {
		/* gcap didn't give any info, switching to old method */
		chip->playback_streams = NUM_PLAYBACK_SD;
		chip->capture_streams = NUM_CAPTURE_SD;
	}
	chip->capture_index_offset = 0;
	chip->playback_index_offset = chip->capture_streams;
	chip->num_streams = chip->playback_streams + chip->capture_streams;

	/* initialize streams */
	err = azx_init_streams(chip);
	if (err < 0) {
		dev_err(card->dev, "failed to initialize streams: %d\n", err);
		return err;
	}

	err = azx_alloc_stream_pages(chip);
	if (err < 0) {
		dev_err(card->dev, "failed to allocate stream pages: %d\n",
			err);
		return err;
	}

	/* initialize chip */
	azx_init_chip(chip, 1);

	/* codec detection */
	if (!bus->codec_mask) {
		dev_err(card->dev, "no codecs found!\n");
		return -ENODEV;
	}

	strcpy(card->driver, "tegra-hda");
	strcpy(card->shortname, "tegra-hda");
	snprintf(card->longname, sizeof(card->longname),
		 "%s at 0x%lx irq %i",
		 card->shortname, bus->addr, bus->irq);

	return 0;
}