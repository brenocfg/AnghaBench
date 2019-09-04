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
typedef  char u8 ;
struct snd_ymfpci_playback_bank {int dummy; } ;
struct snd_ymfpci_effect_bank {int dummy; } ;
struct snd_ymfpci_capture_bank {int dummy; } ;
struct TYPE_4__ {char* area; unsigned long addr; int bytes; } ;
struct snd_ymfpci {int bank_size_playback; int bank_size_capture; int bank_size_effect; long work_size; char* bank_base_playback; unsigned long bank_base_playback_addr; char* bank_base_capture; unsigned long bank_base_capture_addr; char* bank_base_effect; unsigned long bank_base_effect_addr; char* work_base; unsigned long work_base_addr; int spdif_bits; int spdif_pcm_bits; TYPE_2__ work_ptr; struct snd_ymfpci_effect_bank*** bank_effect; struct snd_ymfpci_capture_bank*** bank_capture; struct snd_ymfpci_playback_bank*** bank_playback; TYPE_1__* voices; int /*<<< orphan*/ * ctrl_playback; int /*<<< orphan*/  pci; } ;
typedef  unsigned long dma_addr_t ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_3__ {int number; unsigned long bank_addr; struct snd_ymfpci_playback_bank* bank; } ;

/* Variables and functions */
 unsigned long ALIGN (unsigned long,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 int SNDRV_PCM_DEFAULT_CON_SPDIF ; 
 int YDSXGR_BUF441OUTVOL ; 
 int YDSXGR_EFFCTRLBASE ; 
 int /*<<< orphan*/  YDSXGR_EFFCTRLSIZE ; 
 int YDSXGR_LEGACYOUTVOL ; 
 int YDSXGR_NATIVEADCINVOL ; 
 int YDSXGR_NATIVEDACINVOL ; 
 int YDSXGR_NATIVEDACOUTVOL ; 
 int YDSXGR_PLAYCTRLBASE ; 
 int /*<<< orphan*/  YDSXGR_PLAYCTRLSIZE ; 
 int YDSXGR_PRIADCLOOPVOL ; 
 int YDSXGR_RECCTRLBASE ; 
 int /*<<< orphan*/  YDSXGR_RECCTRLSIZE ; 
 int /*<<< orphan*/  YDSXGR_SPDIFINCTRL ; 
 int /*<<< orphan*/  YDSXGR_SPDIFOUTCTRL ; 
 int /*<<< orphan*/  YDSXGR_SPDIFOUTSTATUS ; 
 int YDSXGR_SPDIFOUTVOL ; 
 int YDSXGR_WORKBASE ; 
 int YDSXGR_WORKSIZE ; 
 int YDSXGR_ZVOUTVOL ; 
 int YDSXG_CAPTURE_VOICES ; 
 long YDSXG_DEFAULT_WORK_SIZE ; 
 int YDSXG_EFFECT_VOICES ; 
 int YDSXG_PLAYBACK_VOICES ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  snd_BUG_ON (int) ; 
 scalar_t__ snd_dma_alloc_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,TYPE_2__*) ; 
 int /*<<< orphan*/  snd_dma_pci_data (int /*<<< orphan*/ ) ; 
 int snd_ymfpci_readl (struct snd_ymfpci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ymfpci_writel (struct snd_ymfpci*,int,int) ; 
 int /*<<< orphan*/  snd_ymfpci_writew (struct snd_ymfpci*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int snd_ymfpci_memalloc(struct snd_ymfpci *chip)
{
	long size, playback_ctrl_size;
	int voice, bank, reg;
	u8 *ptr;
	dma_addr_t ptr_addr;

	playback_ctrl_size = 4 + 4 * YDSXG_PLAYBACK_VOICES;
	chip->bank_size_playback = snd_ymfpci_readl(chip, YDSXGR_PLAYCTRLSIZE) << 2;
	chip->bank_size_capture = snd_ymfpci_readl(chip, YDSXGR_RECCTRLSIZE) << 2;
	chip->bank_size_effect = snd_ymfpci_readl(chip, YDSXGR_EFFCTRLSIZE) << 2;
	chip->work_size = YDSXG_DEFAULT_WORK_SIZE;
	
	size = ALIGN(playback_ctrl_size, 0x100) +
	       ALIGN(chip->bank_size_playback * 2 * YDSXG_PLAYBACK_VOICES, 0x100) +
	       ALIGN(chip->bank_size_capture * 2 * YDSXG_CAPTURE_VOICES, 0x100) +
	       ALIGN(chip->bank_size_effect * 2 * YDSXG_EFFECT_VOICES, 0x100) +
	       chip->work_size;
	/* work_ptr must be aligned to 256 bytes, but it's already
	   covered with the kernel page allocation mechanism */
	if (snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, snd_dma_pci_data(chip->pci),
				size, &chip->work_ptr) < 0) 
		return -ENOMEM;
	ptr = chip->work_ptr.area;
	ptr_addr = chip->work_ptr.addr;
	memset(ptr, 0, size);	/* for sure */

	chip->bank_base_playback = ptr;
	chip->bank_base_playback_addr = ptr_addr;
	chip->ctrl_playback = (__le32 *)ptr;
	chip->ctrl_playback[0] = cpu_to_le32(YDSXG_PLAYBACK_VOICES);
	ptr += ALIGN(playback_ctrl_size, 0x100);
	ptr_addr += ALIGN(playback_ctrl_size, 0x100);
	for (voice = 0; voice < YDSXG_PLAYBACK_VOICES; voice++) {
		chip->voices[voice].number = voice;
		chip->voices[voice].bank = (struct snd_ymfpci_playback_bank *)ptr;
		chip->voices[voice].bank_addr = ptr_addr;
		for (bank = 0; bank < 2; bank++) {
			chip->bank_playback[voice][bank] = (struct snd_ymfpci_playback_bank *)ptr;
			ptr += chip->bank_size_playback;
			ptr_addr += chip->bank_size_playback;
		}
	}
	ptr = (char *)ALIGN((unsigned long)ptr, 0x100);
	ptr_addr = ALIGN(ptr_addr, 0x100);
	chip->bank_base_capture = ptr;
	chip->bank_base_capture_addr = ptr_addr;
	for (voice = 0; voice < YDSXG_CAPTURE_VOICES; voice++)
		for (bank = 0; bank < 2; bank++) {
			chip->bank_capture[voice][bank] = (struct snd_ymfpci_capture_bank *)ptr;
			ptr += chip->bank_size_capture;
			ptr_addr += chip->bank_size_capture;
		}
	ptr = (char *)ALIGN((unsigned long)ptr, 0x100);
	ptr_addr = ALIGN(ptr_addr, 0x100);
	chip->bank_base_effect = ptr;
	chip->bank_base_effect_addr = ptr_addr;
	for (voice = 0; voice < YDSXG_EFFECT_VOICES; voice++)
		for (bank = 0; bank < 2; bank++) {
			chip->bank_effect[voice][bank] = (struct snd_ymfpci_effect_bank *)ptr;
			ptr += chip->bank_size_effect;
			ptr_addr += chip->bank_size_effect;
		}
	ptr = (char *)ALIGN((unsigned long)ptr, 0x100);
	ptr_addr = ALIGN(ptr_addr, 0x100);
	chip->work_base = ptr;
	chip->work_base_addr = ptr_addr;
	
	snd_BUG_ON(ptr + chip->work_size !=
		   chip->work_ptr.area + chip->work_ptr.bytes);

	snd_ymfpci_writel(chip, YDSXGR_PLAYCTRLBASE, chip->bank_base_playback_addr);
	snd_ymfpci_writel(chip, YDSXGR_RECCTRLBASE, chip->bank_base_capture_addr);
	snd_ymfpci_writel(chip, YDSXGR_EFFCTRLBASE, chip->bank_base_effect_addr);
	snd_ymfpci_writel(chip, YDSXGR_WORKBASE, chip->work_base_addr);
	snd_ymfpci_writel(chip, YDSXGR_WORKSIZE, chip->work_size >> 2);

	/* S/PDIF output initialization */
	chip->spdif_bits = chip->spdif_pcm_bits = SNDRV_PCM_DEFAULT_CON_SPDIF & 0xffff;
	snd_ymfpci_writew(chip, YDSXGR_SPDIFOUTCTRL, 0);
	snd_ymfpci_writew(chip, YDSXGR_SPDIFOUTSTATUS, chip->spdif_bits);

	/* S/PDIF input initialization */
	snd_ymfpci_writew(chip, YDSXGR_SPDIFINCTRL, 0);

	/* digital mixer setup */
	for (reg = 0x80; reg < 0xc0; reg += 4)
		snd_ymfpci_writel(chip, reg, 0);
	snd_ymfpci_writel(chip, YDSXGR_NATIVEDACOUTVOL, 0x3fff3fff);
	snd_ymfpci_writel(chip, YDSXGR_BUF441OUTVOL, 0x3fff3fff);
	snd_ymfpci_writel(chip, YDSXGR_ZVOUTVOL, 0x3fff3fff);
	snd_ymfpci_writel(chip, YDSXGR_SPDIFOUTVOL, 0x3fff3fff);
	snd_ymfpci_writel(chip, YDSXGR_NATIVEADCINVOL, 0x3fff3fff);
	snd_ymfpci_writel(chip, YDSXGR_NATIVEDACINVOL, 0x3fff3fff);
	snd_ymfpci_writel(chip, YDSXGR_PRIADCLOOPVOL, 0x3fff3fff);
	snd_ymfpci_writel(chip, YDSXGR_LEGACYOUTVOL, 0x3fff3fff);
	
	return 0;
}