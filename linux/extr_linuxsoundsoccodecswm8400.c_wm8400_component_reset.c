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
struct wm8400_priv {int /*<<< orphan*/  wm8400; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 struct wm8400_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  wm8400_reset_codec_reg_cache (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wm8400_component_reset(struct snd_soc_component *component)
{
	struct wm8400_priv *wm8400 = snd_soc_component_get_drvdata(component);

	wm8400_reset_codec_reg_cache(wm8400->wm8400);
}