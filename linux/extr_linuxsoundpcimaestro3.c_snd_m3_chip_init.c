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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct snd_m3 {unsigned long iobase; int hv_config; scalar_t__ allegro_flag; struct pci_dev* pci; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int ALIAS_10BIT_IO ; 
 int ASSP_0_WS_ENABLE ; 
 int ASSP_CLK_49MHZ_SELECT ; 
 scalar_t__ ASSP_CONTROL_A ; 
 scalar_t__ ASSP_CONTROL_B ; 
 int CLK_DIV_BY_49 ; 
 int CLK_MULT_MODE_SELECT ; 
 int CLK_MULT_MODE_SELECT_2 ; 
 int DISABLE_LEGACY ; 
 int DSP_CLK_36MHZ_SELECT ; 
 int FM_SYNTHESIS_ENABLE ; 
 scalar_t__ HARDWARE_VOL_CTRL ; 
 int HV_BUTTON_FROM_GD ; 
 int HV_CTRL_ENABLE ; 
 scalar_t__ HW_VOL_COUNTER_MASTER ; 
 scalar_t__ HW_VOL_COUNTER_VOICE ; 
 int INT_CLK_MULT_ENABLE ; 
 int INT_CLK_SELECT ; 
 int INT_CLK_SRC_NOT_PCI ; 
 int IN_CLK_12MHZ_SELECT ; 
 int MPU401_IO_ENABLE ; 
 int MPU401_IRQ_ENABLE ; 
 int /*<<< orphan*/  PCI_ALLEGRO_CONFIG ; 
 int /*<<< orphan*/  PCI_LEGACY_AUDIO_CTRL ; 
 int /*<<< orphan*/  PCI_USER_CONFIG ; 
 int PM_CTRL_ENABLE ; 
 int REDUCED_DEBOUNCE ; 
 int RESET_ASSP ; 
 int RUN_ASSP ; 
 scalar_t__ SHADOW_MIX_REG_MASTER ; 
 scalar_t__ SHADOW_MIX_REG_VOICE ; 
 int SOUND_BLASTER_ENABLE ; 
 int USE_PCI_TIMING ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_m3_assp_init (struct snd_m3*) ; 

__attribute__((used)) static int
snd_m3_chip_init(struct snd_m3 *chip)
{
	struct pci_dev *pcidev = chip->pci;
	unsigned long io = chip->iobase;
	u32 n;
	u16 w;
	u8 t; /* makes as much sense as 'n', no? */

	pci_read_config_word(pcidev, PCI_LEGACY_AUDIO_CTRL, &w);
	w &= ~(SOUND_BLASTER_ENABLE|FM_SYNTHESIS_ENABLE|
	       MPU401_IO_ENABLE|MPU401_IRQ_ENABLE|ALIAS_10BIT_IO|
	       DISABLE_LEGACY);
	pci_write_config_word(pcidev, PCI_LEGACY_AUDIO_CTRL, w);

	pci_read_config_dword(pcidev, PCI_ALLEGRO_CONFIG, &n);
	n &= ~(HV_CTRL_ENABLE | REDUCED_DEBOUNCE | HV_BUTTON_FROM_GD);
	n |= chip->hv_config;
	/* For some reason we must always use reduced debounce. */
	n |= REDUCED_DEBOUNCE;
	n |= PM_CTRL_ENABLE | CLK_DIV_BY_49 | USE_PCI_TIMING;
	pci_write_config_dword(pcidev, PCI_ALLEGRO_CONFIG, n);

	outb(RESET_ASSP, chip->iobase + ASSP_CONTROL_B);
	pci_read_config_dword(pcidev, PCI_ALLEGRO_CONFIG, &n);
	n &= ~INT_CLK_SELECT;
	if (!chip->allegro_flag) {
		n &= ~INT_CLK_MULT_ENABLE; 
		n |= INT_CLK_SRC_NOT_PCI;
	}
	n &=  ~( CLK_MULT_MODE_SELECT | CLK_MULT_MODE_SELECT_2 );
	pci_write_config_dword(pcidev, PCI_ALLEGRO_CONFIG, n);

	if (chip->allegro_flag) {
		pci_read_config_dword(pcidev, PCI_USER_CONFIG, &n);
		n |= IN_CLK_12MHZ_SELECT;
		pci_write_config_dword(pcidev, PCI_USER_CONFIG, n);
	}

	t = inb(chip->iobase + ASSP_CONTROL_A);
	t &= ~( DSP_CLK_36MHZ_SELECT  | ASSP_CLK_49MHZ_SELECT);
	t |= ASSP_CLK_49MHZ_SELECT;
	t |= ASSP_0_WS_ENABLE; 
	outb(t, chip->iobase + ASSP_CONTROL_A);

	snd_m3_assp_init(chip); /* download DSP code before starting ASSP below */
	outb(RUN_ASSP, chip->iobase + ASSP_CONTROL_B); 

	outb(0x00, io + HARDWARE_VOL_CTRL);
	outb(0x88, io + SHADOW_MIX_REG_VOICE);
	outb(0x88, io + HW_VOL_COUNTER_VOICE);
	outb(0x88, io + SHADOW_MIX_REG_MASTER);
	outb(0x88, io + HW_VOL_COUNTER_MASTER);

	return 0;
}