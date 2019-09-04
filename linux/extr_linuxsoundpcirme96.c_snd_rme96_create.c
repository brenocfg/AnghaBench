#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rme96 {int irq; int wcreg; int areg; TYPE_1__* card; scalar_t__* vol; scalar_t__ iobase; scalar_t__ capture_periodsize; scalar_t__ playback_periodsize; TYPE_2__* adat_pcm; TYPE_2__* spdif_pcm; int /*<<< orphan*/  rev; scalar_t__ port; struct pci_dev* pci; int /*<<< orphan*/  lock; } ;
struct pci_dev {int irq; scalar_t__ device; } ;
struct TYPE_6__ {scalar_t__ info_flags; int /*<<< orphan*/  name; int /*<<< orphan*/  private_free; struct rme96* private_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 scalar_t__ PCI_DEVICE_ID_RME_DIGI96 ; 
 int RME96_AR_DAC_EN ; 
 int RME96_AR_FREQPAD_1 ; 
 int RME96_AR_PD2 ; 
 scalar_t__ RME96_HAS_ANALOG_OUT (struct rme96*) ; 
 scalar_t__ RME96_IO_ADDITIONAL_REG ; 
 scalar_t__ RME96_IO_CONTROL_REGISTER ; 
 scalar_t__ RME96_IO_RESET_PLAY_POS ; 
 scalar_t__ RME96_IO_RESET_REC_POS ; 
 scalar_t__ RME96_IO_SIZE ; 
 int /*<<< orphan*/  RME96_STOP_BOTH ; 
 int RME96_WCR_FREQ_1 ; 
 int RME96_WCR_INP_0 ; 
 int RME96_WCR_MASTER ; 
 int RME96_WCR_SEL ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 scalar_t__ ioremap_nocache (scalar_t__,scalar_t__) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int /*<<< orphan*/ *) ; 
 int pci_request_regions (struct pci_dev*,char*) ; 
 scalar_t__ pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rme96*) ; 
 int snd_pcm_new (TYPE_1__*,char*,int,int,int,TYPE_2__**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_rme96_apply_dac_volume (struct rme96*) ; 
 int /*<<< orphan*/  snd_rme96_capture_adat_ops ; 
 int /*<<< orphan*/  snd_rme96_capture_spdif_ops ; 
 int snd_rme96_create_switches (TYPE_1__*,struct rme96*) ; 
 int /*<<< orphan*/  snd_rme96_free_adat_pcm ; 
 int /*<<< orphan*/  snd_rme96_free_spdif_pcm ; 
 int /*<<< orphan*/  snd_rme96_interrupt ; 
 int /*<<< orphan*/  snd_rme96_playback_adat_ops ; 
 int /*<<< orphan*/  snd_rme96_playback_spdif_ops ; 
 int /*<<< orphan*/  snd_rme96_proc_init (struct rme96*) ; 
 int /*<<< orphan*/  snd_rme96_reset_dac (struct rme96*) ; 
 int /*<<< orphan*/  snd_rme96_trigger (struct rme96*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int
snd_rme96_create(struct rme96 *rme96)
{
	struct pci_dev *pci = rme96->pci;
	int err;

	rme96->irq = -1;
	spin_lock_init(&rme96->lock);

	if ((err = pci_enable_device(pci)) < 0)
		return err;

	if ((err = pci_request_regions(pci, "RME96")) < 0)
		return err;
	rme96->port = pci_resource_start(rme96->pci, 0);

	rme96->iobase = ioremap_nocache(rme96->port, RME96_IO_SIZE);
	if (!rme96->iobase) {
		dev_err(rme96->card->dev,
			"unable to remap memory region 0x%lx-0x%lx\n",
			rme96->port, rme96->port + RME96_IO_SIZE - 1);
		return -ENOMEM;
	}

	if (request_irq(pci->irq, snd_rme96_interrupt, IRQF_SHARED,
			KBUILD_MODNAME, rme96)) {
		dev_err(rme96->card->dev, "unable to grab IRQ %d\n", pci->irq);
		return -EBUSY;
	}
	rme96->irq = pci->irq;

	/* read the card's revision number */
	pci_read_config_byte(pci, 8, &rme96->rev);	
	
	/* set up ALSA pcm device for S/PDIF */
	if ((err = snd_pcm_new(rme96->card, "Digi96 IEC958", 0,
			       1, 1, &rme96->spdif_pcm)) < 0)
	{
		return err;
	}
	rme96->spdif_pcm->private_data = rme96;
	rme96->spdif_pcm->private_free = snd_rme96_free_spdif_pcm;
	strcpy(rme96->spdif_pcm->name, "Digi96 IEC958");
	snd_pcm_set_ops(rme96->spdif_pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_rme96_playback_spdif_ops);
	snd_pcm_set_ops(rme96->spdif_pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_rme96_capture_spdif_ops);

	rme96->spdif_pcm->info_flags = 0;

	/* set up ALSA pcm device for ADAT */
	if (pci->device == PCI_DEVICE_ID_RME_DIGI96) {
		/* ADAT is not available on the base model */
		rme96->adat_pcm = NULL;
	} else {
		if ((err = snd_pcm_new(rme96->card, "Digi96 ADAT", 1,
				       1, 1, &rme96->adat_pcm)) < 0)
		{
			return err;
		}		
		rme96->adat_pcm->private_data = rme96;
		rme96->adat_pcm->private_free = snd_rme96_free_adat_pcm;
		strcpy(rme96->adat_pcm->name, "Digi96 ADAT");
		snd_pcm_set_ops(rme96->adat_pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_rme96_playback_adat_ops);
		snd_pcm_set_ops(rme96->adat_pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_rme96_capture_adat_ops);
		
		rme96->adat_pcm->info_flags = 0;
	}

	rme96->playback_periodsize = 0;
	rme96->capture_periodsize = 0;
	
	/* make sure playback/capture is stopped, if by some reason active */
	snd_rme96_trigger(rme96, RME96_STOP_BOTH);
	
	/* set default values in registers */
	rme96->wcreg =
		RME96_WCR_FREQ_1 | /* set 44.1 kHz playback */
		RME96_WCR_SEL |    /* normal playback */
		RME96_WCR_MASTER | /* set to master clock mode */
		RME96_WCR_INP_0;   /* set coaxial input */

	rme96->areg = RME96_AR_FREQPAD_1; /* set 44.1 kHz analog capture */

	writel(rme96->wcreg, rme96->iobase + RME96_IO_CONTROL_REGISTER);
	writel(rme96->areg, rme96->iobase + RME96_IO_ADDITIONAL_REG);
	
	/* reset the ADC */
	writel(rme96->areg | RME96_AR_PD2,
	       rme96->iobase + RME96_IO_ADDITIONAL_REG);
	writel(rme96->areg, rme96->iobase + RME96_IO_ADDITIONAL_REG);	

	/* reset and enable the DAC (order is important). */
	snd_rme96_reset_dac(rme96);
	rme96->areg |= RME96_AR_DAC_EN;
	writel(rme96->areg, rme96->iobase + RME96_IO_ADDITIONAL_REG);

	/* reset playback and record buffer pointers */
	writel(0, rme96->iobase + RME96_IO_RESET_PLAY_POS);
	writel(0, rme96->iobase + RME96_IO_RESET_REC_POS);

	/* reset volume */
	rme96->vol[0] = rme96->vol[1] = 0;
	if (RME96_HAS_ANALOG_OUT(rme96)) {
		snd_rme96_apply_dac_volume(rme96);
	}
	
	/* init switch interface */
	if ((err = snd_rme96_create_switches(rme96->card, rme96)) < 0) {
		return err;
	}

        /* init proc interface */
	snd_rme96_proc_init(rme96);
	
	return 0;
}