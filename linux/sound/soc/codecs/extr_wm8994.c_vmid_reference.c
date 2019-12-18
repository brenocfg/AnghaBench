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
struct wm8994_priv {int vmid_refcount; int vmid_mode; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WM8994_ANTIPOP_1 ; 
 int /*<<< orphan*/  WM8994_ANTIPOP_2 ; 
 int WM8994_BIAS_ENA ; 
 int WM8994_BIAS_SRC ; 
 int WM8994_LINEOUT1_DISCH ; 
 int WM8994_LINEOUT2_DISCH ; 
 int /*<<< orphan*/  WM8994_POWER_MANAGEMENT_1 ; 
 int WM8994_STARTUP_BIAS_ENA ; 
 int WM8994_VMID_BUF_ENA ; 
 int WM8994_VMID_DISCH ; 
#define  WM8994_VMID_FORCE 129 
#define  WM8994_VMID_NORMAL 128 
 int WM8994_VMID_RAMP_MASK ; 
 int WM8994_VMID_RAMP_SHIFT ; 
 int WM8994_VMID_SEL_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 struct wm8994_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wm_hubs_vmid_ena (struct snd_soc_component*) ; 

__attribute__((used)) static void vmid_reference(struct snd_soc_component *component)
{
	struct wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);

	pm_runtime_get_sync(component->dev);

	wm8994->vmid_refcount++;

	dev_dbg(component->dev, "Referencing VMID, refcount is now %d\n",
		wm8994->vmid_refcount);

	if (wm8994->vmid_refcount == 1) {
		snd_soc_component_update_bits(component, WM8994_ANTIPOP_1,
				    WM8994_LINEOUT1_DISCH |
				    WM8994_LINEOUT2_DISCH, 0);

		wm_hubs_vmid_ena(component);

		switch (wm8994->vmid_mode) {
		default:
			WARN_ON(NULL == "Invalid VMID mode");
			/* fall through */
		case WM8994_VMID_NORMAL:
			/* Startup bias, VMID ramp & buffer */
			snd_soc_component_update_bits(component, WM8994_ANTIPOP_2,
					    WM8994_BIAS_SRC |
					    WM8994_VMID_DISCH |
					    WM8994_STARTUP_BIAS_ENA |
					    WM8994_VMID_BUF_ENA |
					    WM8994_VMID_RAMP_MASK,
					    WM8994_BIAS_SRC |
					    WM8994_STARTUP_BIAS_ENA |
					    WM8994_VMID_BUF_ENA |
					    (0x2 << WM8994_VMID_RAMP_SHIFT));

			/* Main bias enable, VMID=2x40k */
			snd_soc_component_update_bits(component, WM8994_POWER_MANAGEMENT_1,
					    WM8994_BIAS_ENA |
					    WM8994_VMID_SEL_MASK,
					    WM8994_BIAS_ENA | 0x2);

			msleep(300);

			snd_soc_component_update_bits(component, WM8994_ANTIPOP_2,
					    WM8994_VMID_RAMP_MASK |
					    WM8994_BIAS_SRC,
					    0);
			break;

		case WM8994_VMID_FORCE:
			/* Startup bias, slow VMID ramp & buffer */
			snd_soc_component_update_bits(component, WM8994_ANTIPOP_2,
					    WM8994_BIAS_SRC |
					    WM8994_VMID_DISCH |
					    WM8994_STARTUP_BIAS_ENA |
					    WM8994_VMID_BUF_ENA |
					    WM8994_VMID_RAMP_MASK,
					    WM8994_BIAS_SRC |
					    WM8994_STARTUP_BIAS_ENA |
					    WM8994_VMID_BUF_ENA |
					    (0x2 << WM8994_VMID_RAMP_SHIFT));

			/* Main bias enable, VMID=2x40k */
			snd_soc_component_update_bits(component, WM8994_POWER_MANAGEMENT_1,
					    WM8994_BIAS_ENA |
					    WM8994_VMID_SEL_MASK,
					    WM8994_BIAS_ENA | 0x2);

			msleep(400);

			snd_soc_component_update_bits(component, WM8994_ANTIPOP_2,
					    WM8994_VMID_RAMP_MASK |
					    WM8994_BIAS_SRC,
					    0);
			break;
		}
	}
}