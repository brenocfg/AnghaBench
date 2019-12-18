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
typedef  int u32 ;
struct trn_conf {int /*<<< orphan*/  vm_pgt_phys; int /*<<< orphan*/  member_0; } ;
struct hw {scalar_t__ model; } ;
struct daio_conf {int /*<<< orphan*/  msr; int /*<<< orphan*/  member_0; } ;
struct dac_conf {int /*<<< orphan*/  msr; int /*<<< orphan*/  member_0; } ;
struct card_conf {int /*<<< orphan*/  msr; int /*<<< orphan*/  vm_pgt_phys; int /*<<< orphan*/  rsr; } ;
struct adc_conf {scalar_t__ mic20db; int /*<<< orphan*/  input; int /*<<< orphan*/  msr; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADC_LINEIN ; 
 scalar_t__ CTSB1270 ; 
 int /*<<< orphan*/  GCTL_DBP ; 
 int /*<<< orphan*/  GCTL_DPC ; 
 int /*<<< orphan*/  GCTL_FBP ; 
 int /*<<< orphan*/  GCTL_TBP ; 
 int /*<<< orphan*/  GIE ; 
 int /*<<< orphan*/  GLOBAL_CNTL_GCTL ; 
 int /*<<< orphan*/  GPIO_CTRL ; 
 int /*<<< orphan*/  MIXER_AR_ENABLE ; 
 int /*<<< orphan*/  SRC_IP ; 
 int /*<<< orphan*/  SRC_MCTL ; 
 int hw_adc_init (struct hw*,struct adc_conf*) ; 
 int hw_auto_init (struct hw*) ; 
 int hw_card_start (struct hw*) ; 
 int hw_dac_init (struct hw*,struct dac_conf*) ; 
 int hw_daio_init (struct hw*,struct daio_conf*) ; 
 int hw_pll_init (struct hw*,int /*<<< orphan*/ ) ; 
 void* hw_read_20kx (struct hw*,int /*<<< orphan*/ ) ; 
 int hw_trn_init (struct hw*,struct trn_conf*) ; 
 int /*<<< orphan*/  hw_write_20kx (struct hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_field (unsigned int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hw_card_init(struct hw *hw, struct card_conf *info)
{
	int err;
	unsigned int gctl;
	u32 data = 0;
	struct dac_conf dac_info = {0};
	struct adc_conf adc_info = {0};
	struct daio_conf daio_info = {0};
	struct trn_conf trn_info = {0};

	/* Get PCI io port/memory base address and
	 * do 20kx core switch if needed. */
	err = hw_card_start(hw);
	if (err)
		return err;

	/* PLL init */
	err = hw_pll_init(hw, info->rsr);
	if (err < 0)
		return err;

	/* kick off auto-init */
	err = hw_auto_init(hw);
	if (err < 0)
		return err;

	gctl = hw_read_20kx(hw, GLOBAL_CNTL_GCTL);
	set_field(&gctl, GCTL_DBP, 1);
	set_field(&gctl, GCTL_TBP, 1);
	set_field(&gctl, GCTL_FBP, 1);
	set_field(&gctl, GCTL_DPC, 0);
	hw_write_20kx(hw, GLOBAL_CNTL_GCTL, gctl);

	/* Reset all global pending interrupts */
	hw_write_20kx(hw, GIE, 0);
	/* Reset all SRC pending interrupts */
	hw_write_20kx(hw, SRC_IP, 0);

	if (hw->model != CTSB1270) {
		/* TODO: detect the card ID and configure GPIO accordingly. */
		/* Configures GPIO (0xD802 0x98028) */
		/*hw_write_20kx(hw, GPIO_CTRL, 0x7F07);*/
		/* Configures GPIO (SB0880) */
		/*hw_write_20kx(hw, GPIO_CTRL, 0xFF07);*/
		hw_write_20kx(hw, GPIO_CTRL, 0xD802);
	} else {
		hw_write_20kx(hw, GPIO_CTRL, 0x9E5F);
	}
	/* Enable audio ring */
	hw_write_20kx(hw, MIXER_AR_ENABLE, 0x01);

	trn_info.vm_pgt_phys = info->vm_pgt_phys;
	err = hw_trn_init(hw, &trn_info);
	if (err < 0)
		return err;

	daio_info.msr = info->msr;
	err = hw_daio_init(hw, &daio_info);
	if (err < 0)
		return err;

	dac_info.msr = info->msr;
	err = hw_dac_init(hw, &dac_info);
	if (err < 0)
		return err;

	adc_info.msr = info->msr;
	adc_info.input = ADC_LINEIN;
	adc_info.mic20db = 0;
	err = hw_adc_init(hw, &adc_info);
	if (err < 0)
		return err;

	data = hw_read_20kx(hw, SRC_MCTL);
	data |= 0x1; /* Enables input from the audio ring */
	hw_write_20kx(hw, SRC_MCTL, data);

	return 0;
}