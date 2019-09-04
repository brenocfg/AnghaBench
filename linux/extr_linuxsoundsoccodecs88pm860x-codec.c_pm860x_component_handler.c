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
struct TYPE_3__ {int hs_shrt; int hook_det; int lo_shrt; int hp_det; int mic_det; int /*<<< orphan*/  mic_jack; int /*<<< orphan*/  hp_jack; } ;
struct pm860x_priv {TYPE_2__* component; TYPE_1__ det; int /*<<< orphan*/  i2c; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int HEADSET_STATUS ; 
 int HOOK_STATUS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int MIC_STATUS ; 
 int /*<<< orphan*/  REG_SHORTS ; 
 int /*<<< orphan*/  REG_STATUS_1 ; 
 int SHORT_HS1 ; 
 int SHORT_HS2 ; 
 int SHORT_LO1 ; 
 int SHORT_LO2 ; 
 int SND_JACK_HEADPHONE ; 
 int SND_JACK_MICROPHONE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int pm860x_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_jack_report (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  trace_snd_soc_jack_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t pm860x_component_handler(int irq, void *data)
{
	struct pm860x_priv *pm860x = data;
	int status, shrt, report = 0, mic_report = 0;
	int mask;

	status = pm860x_reg_read(pm860x->i2c, REG_STATUS_1);
	shrt = pm860x_reg_read(pm860x->i2c, REG_SHORTS);
	mask = pm860x->det.hs_shrt | pm860x->det.hook_det | pm860x->det.lo_shrt
		| pm860x->det.hp_det;

#ifndef CONFIG_SND_SOC_88PM860X_MODULE
	if (status & (HEADSET_STATUS | MIC_STATUS | SHORT_HS1 | SHORT_HS2 |
		      SHORT_LO1 | SHORT_LO2))
		trace_snd_soc_jack_irq(dev_name(pm860x->component->dev));
#endif

	if ((pm860x->det.hp_det & SND_JACK_HEADPHONE)
		&& (status & HEADSET_STATUS))
		report |= SND_JACK_HEADPHONE;

	if ((pm860x->det.mic_det & SND_JACK_MICROPHONE)
		&& (status & MIC_STATUS))
		mic_report |= SND_JACK_MICROPHONE;

	if (pm860x->det.hs_shrt && (shrt & (SHORT_HS1 | SHORT_HS2)))
		report |= pm860x->det.hs_shrt;

	if (pm860x->det.hook_det && (status & HOOK_STATUS))
		report |= pm860x->det.hook_det;

	if (pm860x->det.lo_shrt && (shrt & (SHORT_LO1 | SHORT_LO2)))
		report |= pm860x->det.lo_shrt;

	if (report)
		snd_soc_jack_report(pm860x->det.hp_jack, report, mask);
	if (mic_report)
		snd_soc_jack_report(pm860x->det.mic_jack, SND_JACK_MICROPHONE,
				    SND_JACK_MICROPHONE);

	dev_dbg(pm860x->component->dev, "headphone report:0x%x, mask:%x\n",
		report, mask);
	dev_dbg(pm860x->component->dev, "microphone report:0x%x\n", mic_report);
	return IRQ_HANDLED;
}