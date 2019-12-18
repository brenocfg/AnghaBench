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
typedef  int u16 ;
struct snd_card {char* shortname; int /*<<< orphan*/  longname; int /*<<< orphan*/  driver; int /*<<< orphan*/  dev; } ;
struct pci_dev {int no_64bit_msi; scalar_t__ vendor; int revision; int /*<<< orphan*/  dev; } ;
struct hdac_bus {int /*<<< orphan*/  irq; int /*<<< orphan*/  addr; int /*<<< orphan*/  codec_mask; scalar_t__ ppcap; int /*<<< orphan*/ * remap_addr; } ;
struct azx {int dev_index; int driver_type; int region_requested; int gts_present; int driver_caps; int align_buffer_size; unsigned short capture_streams; unsigned short playback_streams; unsigned short playback_index_offset; unsigned short num_streams; struct snd_card* card; scalar_t__ capture_index_offset; struct pci_dev* pci; scalar_t__ msi; } ;

/* Variables and functions */
 unsigned short ATIHDMI_NUM_CAPTURE ; 
 unsigned short ATIHDMI_NUM_PLAYBACK ; 
 int AZX_DCAPS_NO_64BIT ; 
 int AZX_DCAPS_NO_ALIGN_BUFSIZE ; 
 int AZX_DCAPS_NO_MSI64 ; 
 int AZX_DCAPS_SEPARATE_STREAM_TAG ; 
#define  AZX_DRIVER_ATIHDMI 131 
#define  AZX_DRIVER_ATIHDMI_NS 130 
#define  AZX_DRIVER_GENERIC 129 
 int AZX_DRIVER_SKL ; 
#define  AZX_DRIVER_ULI 128 
 unsigned short AZX_GCAP_64OK ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int EBUSY ; 
 int ENODEV ; 
 int ENXIO ; 
 int /*<<< orphan*/  GCAP ; 
 unsigned short ICH6_NUM_CAPTURE ; 
 unsigned short ICH6_NUM_PLAYBACK ; 
 int /*<<< orphan*/  PCI_BASE_ADDRESS_1 ; 
 int /*<<< orphan*/  PCI_DEVICE_ID_ATI_SBX00_SMBUS ; 
 scalar_t__ PCI_VENDOR_ID_AMD ; 
 scalar_t__ PCI_VENDOR_ID_ATI ; 
 scalar_t__ PCI_VENDOR_ID_NVIDIA ; 
 unsigned short ULI_NUM_CAPTURE ; 
 unsigned short ULI_NUM_PLAYBACK ; 
 int /*<<< orphan*/  X86_FEATURE_ART ; 
 scalar_t__ align_buffer_size ; 
 scalar_t__ azx_acquire_irq (struct azx*,int /*<<< orphan*/ ) ; 
 int azx_alloc_stream_pages (struct azx*) ; 
 struct hdac_bus* azx_bus (struct azx*) ; 
 int /*<<< orphan*/  azx_init_pci (struct azx*) ; 
 int azx_init_streams (struct azx*) ; 
 unsigned short azx_readw (struct azx*,int /*<<< orphan*/ ) ; 
 scalar_t__ boot_cpu_has (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dma_set_coherent_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_set_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * driver_short_names ; 
 int /*<<< orphan*/  hda_intel_init_chip (struct azx*,int) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 scalar_t__ pci_enable_msi (struct pci_dev*) ; 
 struct pci_dev* pci_get_device (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pci_ioremap_bar (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int,int*) ; 
 int pci_request_regions (struct pci_dev*,char*) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int,int) ; 
 int* probe_only ; 
 int /*<<< orphan*/  snd_hdac_bus_parse_capabilities (struct hdac_bus*) ; 
 int /*<<< orphan*/  snd_hdac_i915_set_bclk (struct hdac_bus*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int azx_first_init(struct azx *chip)
{
	int dev = chip->dev_index;
	struct pci_dev *pci = chip->pci;
	struct snd_card *card = chip->card;
	struct hdac_bus *bus = azx_bus(chip);
	int err;
	unsigned short gcap;
	unsigned int dma_bits = 64;

#if BITS_PER_LONG != 64
	/* Fix up base address on ULI M5461 */
	if (chip->driver_type == AZX_DRIVER_ULI) {
		u16 tmp3;
		pci_read_config_word(pci, 0x40, &tmp3);
		pci_write_config_word(pci, 0x40, tmp3 | 0x10);
		pci_write_config_dword(pci, PCI_BASE_ADDRESS_1, 0);
	}
#endif

	err = pci_request_regions(pci, "ICH HD audio");
	if (err < 0)
		return err;
	chip->region_requested = 1;

	bus->addr = pci_resource_start(pci, 0);
	bus->remap_addr = pci_ioremap_bar(pci, 0);
	if (bus->remap_addr == NULL) {
		dev_err(card->dev, "ioremap error\n");
		return -ENXIO;
	}

	if (chip->driver_type == AZX_DRIVER_SKL)
		snd_hdac_bus_parse_capabilities(bus);

	/*
	 * Some Intel CPUs has always running timer (ART) feature and
	 * controller may have Global time sync reporting capability, so
	 * check both of these before declaring synchronized time reporting
	 * capability SNDRV_PCM_INFO_HAS_LINK_SYNCHRONIZED_ATIME
	 */
	chip->gts_present = false;

#ifdef CONFIG_X86
	if (bus->ppcap && boot_cpu_has(X86_FEATURE_ART))
		chip->gts_present = true;
#endif

	if (chip->msi) {
		if (chip->driver_caps & AZX_DCAPS_NO_MSI64) {
			dev_dbg(card->dev, "Disabling 64bit MSI\n");
			pci->no_64bit_msi = true;
		}
		if (pci_enable_msi(pci) < 0)
			chip->msi = 0;
	}

	pci_set_master(pci);
	synchronize_irq(bus->irq);

	gcap = azx_readw(chip, GCAP);
	dev_dbg(card->dev, "chipset global capabilities = 0x%x\n", gcap);

	/* AMD devices support 40 or 48bit DMA, take the safe one */
	if (chip->pci->vendor == PCI_VENDOR_ID_AMD)
		dma_bits = 40;

	/* disable SB600 64bit support for safety */
	if (chip->pci->vendor == PCI_VENDOR_ID_ATI) {
		struct pci_dev *p_smbus;
		dma_bits = 40;
		p_smbus = pci_get_device(PCI_VENDOR_ID_ATI,
					 PCI_DEVICE_ID_ATI_SBX00_SMBUS,
					 NULL);
		if (p_smbus) {
			if (p_smbus->revision < 0x30)
				gcap &= ~AZX_GCAP_64OK;
			pci_dev_put(p_smbus);
		}
	}

	/* NVidia hardware normally only supports up to 40 bits of DMA */
	if (chip->pci->vendor == PCI_VENDOR_ID_NVIDIA)
		dma_bits = 40;

	/* disable 64bit DMA address on some devices */
	if (chip->driver_caps & AZX_DCAPS_NO_64BIT) {
		dev_dbg(card->dev, "Disabling 64bit DMA\n");
		gcap &= ~AZX_GCAP_64OK;
	}

	/* disable buffer size rounding to 128-byte multiples if supported */
	if (align_buffer_size >= 0)
		chip->align_buffer_size = !!align_buffer_size;
	else {
		if (chip->driver_caps & AZX_DCAPS_NO_ALIGN_BUFSIZE)
			chip->align_buffer_size = 0;
		else
			chip->align_buffer_size = 1;
	}

	/* allow 64bit DMA address if supported by H/W */
	if (!(gcap & AZX_GCAP_64OK))
		dma_bits = 32;
	if (!dma_set_mask(&pci->dev, DMA_BIT_MASK(dma_bits))) {
		dma_set_coherent_mask(&pci->dev, DMA_BIT_MASK(dma_bits));
	} else {
		dma_set_mask(&pci->dev, DMA_BIT_MASK(32));
		dma_set_coherent_mask(&pci->dev, DMA_BIT_MASK(32));
	}

	/* read number of streams from GCAP register instead of using
	 * hardcoded value
	 */
	chip->capture_streams = (gcap >> 8) & 0x0f;
	chip->playback_streams = (gcap >> 12) & 0x0f;
	if (!chip->playback_streams && !chip->capture_streams) {
		/* gcap didn't give any info, switching to old method */

		switch (chip->driver_type) {
		case AZX_DRIVER_ULI:
			chip->playback_streams = ULI_NUM_PLAYBACK;
			chip->capture_streams = ULI_NUM_CAPTURE;
			break;
		case AZX_DRIVER_ATIHDMI:
		case AZX_DRIVER_ATIHDMI_NS:
			chip->playback_streams = ATIHDMI_NUM_PLAYBACK;
			chip->capture_streams = ATIHDMI_NUM_CAPTURE;
			break;
		case AZX_DRIVER_GENERIC:
		default:
			chip->playback_streams = ICH6_NUM_PLAYBACK;
			chip->capture_streams = ICH6_NUM_CAPTURE;
			break;
		}
	}
	chip->capture_index_offset = 0;
	chip->playback_index_offset = chip->capture_streams;
	chip->num_streams = chip->playback_streams + chip->capture_streams;

	/* sanity check for the SDxCTL.STRM field overflow */
	if (chip->num_streams > 15 &&
	    (chip->driver_caps & AZX_DCAPS_SEPARATE_STREAM_TAG) == 0) {
		dev_warn(chip->card->dev, "number of I/O streams is %d, "
			 "forcing separate stream tags", chip->num_streams);
		chip->driver_caps |= AZX_DCAPS_SEPARATE_STREAM_TAG;
	}

	/* initialize streams */
	err = azx_init_streams(chip);
	if (err < 0)
		return err;

	err = azx_alloc_stream_pages(chip);
	if (err < 0)
		return err;

	/* initialize chip */
	azx_init_pci(chip);

	snd_hdac_i915_set_bclk(bus);

	hda_intel_init_chip(chip, (probe_only[dev] & 2) == 0);

	/* codec detection */
	if (!azx_bus(chip)->codec_mask) {
		dev_err(card->dev, "no codecs found!\n");
		return -ENODEV;
	}

	if (azx_acquire_irq(chip, 0) < 0)
		return -EBUSY;

	strcpy(card->driver, "HDA-Intel");
	strlcpy(card->shortname, driver_short_names[chip->driver_type],
		sizeof(card->shortname));
	snprintf(card->longname, sizeof(card->longname),
		 "%s at 0x%lx irq %i",
		 card->shortname, bus->addr, bus->irq);

	return 0;
}