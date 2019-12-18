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
struct wm5100_priv {int dummy; } ;
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 int WM5100_CLKGEN_ERR_ASYNC_STS ; 
 int WM5100_CLKGEN_ERR_STS ; 
 int /*<<< orphan*/  WM5100_INTERRUPT_RAW_STATUS_3 ; 
 int /*<<< orphan*/  WM5100_INTERRUPT_RAW_STATUS_4 ; 
 int WM5100_SPK_SHUTDOWN_STS ; 
 int WM5100_SPK_SHUTDOWN_WARN_STS ; 
 struct wm5100_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm5100_log_status3 (struct wm5100_priv*,int) ; 
 int /*<<< orphan*/  wm5100_log_status4 (struct wm5100_priv*,int) ; 

__attribute__((used)) static int wm5100_post_ev(struct snd_soc_dapm_widget *w,
			  struct snd_kcontrol *kcontrol,
			  int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct wm5100_priv *wm5100 = snd_soc_component_get_drvdata(component);
	int ret;

	ret = snd_soc_component_read32(component, WM5100_INTERRUPT_RAW_STATUS_3);
	ret &= WM5100_SPK_SHUTDOWN_WARN_STS |
		WM5100_SPK_SHUTDOWN_STS | WM5100_CLKGEN_ERR_STS |
		WM5100_CLKGEN_ERR_ASYNC_STS;
	wm5100_log_status3(wm5100, ret);

	ret = snd_soc_component_read32(component, WM5100_INTERRUPT_RAW_STATUS_4);
	wm5100_log_status4(wm5100, ret);

	return 0;
}