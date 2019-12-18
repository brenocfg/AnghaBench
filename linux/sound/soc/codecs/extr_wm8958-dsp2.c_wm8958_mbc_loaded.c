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
struct wm8994_priv {int /*<<< orphan*/  fw_lock; struct firmware const* mbc; } ;
struct snd_soc_component {int dummy; } ;
struct firmware {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct wm8994_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 scalar_t__ wm8958_dsp2_fw (struct snd_soc_component*,char*,struct firmware const*,int) ; 

__attribute__((used)) static void wm8958_mbc_loaded(const struct firmware *fw, void *context)
{
	struct snd_soc_component *component = context;
	struct wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);

	if (fw && (wm8958_dsp2_fw(component, "MBC", fw, true) == 0)) {
		mutex_lock(&wm8994->fw_lock);
		wm8994->mbc = fw;
		mutex_unlock(&wm8994->fw_lock);
	}
}