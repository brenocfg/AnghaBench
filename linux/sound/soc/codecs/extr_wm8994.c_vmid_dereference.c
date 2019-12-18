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
struct TYPE_2__ {scalar_t__ lineout2_se; scalar_t__ lineout1_se; } ;
struct wm8994_priv {scalar_t__ vmid_refcount; TYPE_1__ hubs; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8994_ANTIPOP_1 ; 
 int /*<<< orphan*/  WM8994_ANTIPOP_2 ; 
 int WM8994_BIAS_SRC ; 
 int WM8994_LINEOUT1N_ENA ; 
 int WM8994_LINEOUT1P_ENA ; 
 int WM8994_LINEOUT1_DISCH ; 
 int WM8994_LINEOUT2N_ENA ; 
 int WM8994_LINEOUT2P_ENA ; 
 int WM8994_LINEOUT2_DISCH ; 
 int /*<<< orphan*/  WM8994_POWER_MANAGEMENT_1 ; 
 int /*<<< orphan*/  WM8994_POWER_MANAGEMENT_3 ; 
 int WM8994_STARTUP_BIAS_ENA ; 
 int WM8994_VMID_BUF_ENA ; 
 int WM8994_VMID_DISCH ; 
 int WM8994_VMID_RAMP_MASK ; 
 int WM8994_VMID_SEL_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 struct wm8994_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void vmid_dereference(struct snd_soc_component *component)
{
	struct wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);

	wm8994->vmid_refcount--;

	dev_dbg(component->dev, "Dereferencing VMID, refcount is now %d\n",
		wm8994->vmid_refcount);

	if (wm8994->vmid_refcount == 0) {
		if (wm8994->hubs.lineout1_se)
			snd_soc_component_update_bits(component, WM8994_POWER_MANAGEMENT_3,
					    WM8994_LINEOUT1N_ENA |
					    WM8994_LINEOUT1P_ENA,
					    WM8994_LINEOUT1N_ENA |
					    WM8994_LINEOUT1P_ENA);

		if (wm8994->hubs.lineout2_se)
			snd_soc_component_update_bits(component, WM8994_POWER_MANAGEMENT_3,
					    WM8994_LINEOUT2N_ENA |
					    WM8994_LINEOUT2P_ENA,
					    WM8994_LINEOUT2N_ENA |
					    WM8994_LINEOUT2P_ENA);

		/* Start discharging VMID */
		snd_soc_component_update_bits(component, WM8994_ANTIPOP_2,
				    WM8994_BIAS_SRC |
				    WM8994_VMID_DISCH,
				    WM8994_BIAS_SRC |
				    WM8994_VMID_DISCH);

		snd_soc_component_update_bits(component, WM8994_POWER_MANAGEMENT_1,
				    WM8994_VMID_SEL_MASK, 0);

		msleep(400);

		/* Active discharge */
		snd_soc_component_update_bits(component, WM8994_ANTIPOP_1,
				    WM8994_LINEOUT1_DISCH |
				    WM8994_LINEOUT2_DISCH,
				    WM8994_LINEOUT1_DISCH |
				    WM8994_LINEOUT2_DISCH);

		snd_soc_component_update_bits(component, WM8994_POWER_MANAGEMENT_3,
				    WM8994_LINEOUT1N_ENA |
				    WM8994_LINEOUT1P_ENA |
				    WM8994_LINEOUT2N_ENA |
				    WM8994_LINEOUT2P_ENA, 0);

		/* Switch off startup biases */
		snd_soc_component_update_bits(component, WM8994_ANTIPOP_2,
				    WM8994_BIAS_SRC |
				    WM8994_STARTUP_BIAS_ENA |
				    WM8994_VMID_BUF_ENA |
				    WM8994_VMID_RAMP_MASK, 0);

		snd_soc_component_update_bits(component, WM8994_POWER_MANAGEMENT_1,
				    WM8994_VMID_SEL_MASK, 0);
	}

	pm_runtime_put(component->dev);
}