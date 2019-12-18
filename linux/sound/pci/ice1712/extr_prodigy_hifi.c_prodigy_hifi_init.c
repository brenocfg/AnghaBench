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
struct TYPE_2__ {scalar_t__* saved; } ;
struct snd_ice1712 {int vt1724; int num_total_dacs; int num_total_adcs; int akm_codecs; int pm_suspend_enabled; int /*<<< orphan*/ * pm_resume; struct prodigy_hifi_spec* spec; void* akm; TYPE_1__ gpio; scalar_t__ vt1720; } ;
struct snd_akm4xxx {int dummy; } ;
struct prodigy_hifi_spec {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (unsigned short*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  WM_ADC_ATTEN_L 147 
#define  WM_ADC_ATTEN_R 146 
#define  WM_ADC_INT 145 
#define  WM_ADC_MUX 144 
#define  WM_ALC_CTRL1 143 
#define  WM_ALC_CTRL2 142 
#define  WM_ALC_CTRL3 141 
#define  WM_DAC_ATTEN_L 140 
#define  WM_DAC_ATTEN_R 139 
#define  WM_DAC_CTRL1 138 
#define  WM_DAC_CTRL2 137 
#define  WM_DAC_INT 136 
#define  WM_DAC_MASTER 135 
#define  WM_DAC_MUTE 134 
#define  WM_HP_ATTEN_L 133 
#define  WM_HP_ATTEN_R 132 
#define  WM_MASTER_CTRL 131 
#define  WM_NOISE_GATE 130 
#define  WM_OUT_MUX 129 
#define  WM_PHASE_SWAP 128 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prodigy_hifi_resume ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 int /*<<< orphan*/  wm8766_init (struct snd_ice1712*) ; 
 int /*<<< orphan*/  wm8776_init (struct snd_ice1712*) ; 
 int /*<<< orphan*/  wm_put (struct snd_ice1712*,unsigned short,unsigned short) ; 

__attribute__((used)) static int prodigy_hifi_init(struct snd_ice1712 *ice)
{
	static unsigned short wm8776_defaults[] = {
		WM_MASTER_CTRL,  0x0022, /* 256fs, slave mode */
		WM_DAC_INT,	0x0022,	/* I2S, normal polarity, 24bit */
		WM_ADC_INT,	0x0022,	/* I2S, normal polarity, 24bit */
		WM_DAC_CTRL1,	0x0090,	/* DAC L/R */
		WM_OUT_MUX,	0x0001,	/* OUT DAC */
		WM_HP_ATTEN_L,	0x0179,	/* HP 0dB */
		WM_HP_ATTEN_R,	0x0179,	/* HP 0dB */
		WM_DAC_ATTEN_L,	0x0000,	/* DAC 0dB */
		WM_DAC_ATTEN_L,	0x0100,	/* DAC 0dB */
		WM_DAC_ATTEN_R,	0x0000,	/* DAC 0dB */
		WM_DAC_ATTEN_R,	0x0100,	/* DAC 0dB */
		WM_PHASE_SWAP,	0x0000,	/* phase normal */
#if 0
		WM_DAC_MASTER,	0x0100,	/* DAC master muted */
#endif
		WM_DAC_CTRL2,	0x0000,	/* no deemphasis, no ZFLG */
		WM_ADC_ATTEN_L,	0x0000,	/* ADC muted */
		WM_ADC_ATTEN_R,	0x0000,	/* ADC muted */
#if 1
		WM_ALC_CTRL1,	0x007b,	/* */
		WM_ALC_CTRL2,	0x0000,	/* */
		WM_ALC_CTRL3,	0x0000,	/* */
		WM_NOISE_GATE,	0x0000,	/* */
#endif
		WM_DAC_MUTE,	0x0000,	/* DAC unmute */
		WM_ADC_MUX,	0x0003,	/* ADC unmute, both CD/Line On */
	};
	struct prodigy_hifi_spec *spec;
	unsigned int i;

	ice->vt1720 = 0;
	ice->vt1724 = 1;

	ice->num_total_dacs = 8;
	ice->num_total_adcs = 1;

	/* HACK - use this as the SPDIF source.
	* don't call snd_ice1712_gpio_get/put(), otherwise it's overwritten
	*/
	ice->gpio.saved[0] = 0;
	/* to remember the register values */

	ice->akm = kzalloc(sizeof(struct snd_akm4xxx), GFP_KERNEL);
	if (! ice->akm)
		return -ENOMEM;
	ice->akm_codecs = 1;

	spec = kzalloc(sizeof(*spec), GFP_KERNEL);
	if (!spec)
		return -ENOMEM;
	ice->spec = spec;

	/* initialize WM8776 codec */
	wm8776_init(ice);
	schedule_timeout_uninterruptible(1);
	for (i = 0; i < ARRAY_SIZE(wm8776_defaults); i += 2)
		wm_put(ice, wm8776_defaults[i], wm8776_defaults[i + 1]);

	wm8766_init(ice);

#ifdef CONFIG_PM_SLEEP
	ice->pm_resume = &prodigy_hifi_resume;
	ice->pm_suspend_enabled = 1;
#endif

	return 0;
}