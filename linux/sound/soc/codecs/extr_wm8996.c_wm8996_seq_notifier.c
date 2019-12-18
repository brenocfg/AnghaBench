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
struct wm8996_priv {int dcs_pending; int hpout_pending; int hpout_ena; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
typedef  enum snd_soc_dapm_type { ____Placeholder_snd_soc_dapm_type } snd_soc_dapm_type ;

/* Variables and functions */
 int HPOUT1L ; 
 int HPOUT1R ; 
 int HPOUT2L ; 
 int HPOUT2R ; 
 int /*<<< orphan*/  WM8996_ANALOGUE_HP_1 ; 
 int /*<<< orphan*/  WM8996_ANALOGUE_HP_2 ; 
 int WM8996_DCS_TRIG_STARTUP_0_SHIFT ; 
 int WM8996_HPOUT1L_DLY ; 
 int WM8996_HPOUT1L_OUTP ; 
 int WM8996_HPOUT1L_RMV_SHORT ; 
 int WM8996_HPOUT1R_DLY ; 
 int WM8996_HPOUT1R_OUTP ; 
 int WM8996_HPOUT1R_RMV_SHORT ; 
 int WM8996_HPOUT2L_DLY ; 
 int WM8996_HPOUT2L_OUTP ; 
 int WM8996_HPOUT2L_RMV_SHORT ; 
 int WM8996_HPOUT2R_DLY ; 
 int WM8996_HPOUT2R_OUTP ; 
 int WM8996_HPOUT2R_RMV_SHORT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 struct wm8996_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wait_for_dc_servo (struct snd_soc_component*,int) ; 

__attribute__((used)) static void wm8996_seq_notifier(struct snd_soc_component *component,
				enum snd_soc_dapm_type event, int subseq)
{
	struct wm8996_priv *wm8996 = snd_soc_component_get_drvdata(component);
	u16 val, mask;

	/* Complete any pending DC servo starts */
	if (wm8996->dcs_pending) {
		dev_dbg(component->dev, "Starting DC servo for %x\n",
			wm8996->dcs_pending);

		/* Trigger a startup sequence */
		wait_for_dc_servo(component, wm8996->dcs_pending
				         << WM8996_DCS_TRIG_STARTUP_0_SHIFT);

		wm8996->dcs_pending = 0;
	}

	if (wm8996->hpout_pending != wm8996->hpout_ena) {
		dev_dbg(component->dev, "Applying RMV_SHORTs %x->%x\n",
			wm8996->hpout_ena, wm8996->hpout_pending);

		val = 0;
		mask = 0;
		if (wm8996->hpout_pending & HPOUT1L) {
			val |= WM8996_HPOUT1L_RMV_SHORT | WM8996_HPOUT1L_OUTP;
			mask |= WM8996_HPOUT1L_RMV_SHORT | WM8996_HPOUT1L_OUTP;
		} else {
			mask |= WM8996_HPOUT1L_RMV_SHORT |
				WM8996_HPOUT1L_OUTP |
				WM8996_HPOUT1L_DLY;
		}

		if (wm8996->hpout_pending & HPOUT1R) {
			val |= WM8996_HPOUT1R_RMV_SHORT | WM8996_HPOUT1R_OUTP;
			mask |= WM8996_HPOUT1R_RMV_SHORT | WM8996_HPOUT1R_OUTP;
		} else {
			mask |= WM8996_HPOUT1R_RMV_SHORT |
				WM8996_HPOUT1R_OUTP |
				WM8996_HPOUT1R_DLY;
		}

		snd_soc_component_update_bits(component, WM8996_ANALOGUE_HP_1, mask, val);

		val = 0;
		mask = 0;
		if (wm8996->hpout_pending & HPOUT2L) {
			val |= WM8996_HPOUT2L_RMV_SHORT | WM8996_HPOUT2L_OUTP;
			mask |= WM8996_HPOUT2L_RMV_SHORT | WM8996_HPOUT2L_OUTP;
		} else {
			mask |= WM8996_HPOUT2L_RMV_SHORT |
				WM8996_HPOUT2L_OUTP |
				WM8996_HPOUT2L_DLY;
		}

		if (wm8996->hpout_pending & HPOUT2R) {
			val |= WM8996_HPOUT2R_RMV_SHORT | WM8996_HPOUT2R_OUTP;
			mask |= WM8996_HPOUT2R_RMV_SHORT | WM8996_HPOUT2R_OUTP;
		} else {
			mask |= WM8996_HPOUT2R_RMV_SHORT |
				WM8996_HPOUT2R_OUTP |
				WM8996_HPOUT2R_DLY;
		}

		snd_soc_component_update_bits(component, WM8996_ANALOGUE_HP_2, mask, val);

		wm8996->hpout_ena = wm8996->hpout_pending;
	}
}