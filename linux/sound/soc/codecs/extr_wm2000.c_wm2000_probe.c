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
struct wm2000_priv {int dummy; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct wm2000_priv* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm2000_anc_set_mode (struct wm2000_priv*) ; 

__attribute__((used)) static int wm2000_probe(struct snd_soc_component *component)
{
	struct wm2000_priv *wm2000 = dev_get_drvdata(component->dev);

	/* This will trigger a transition to standby mode by default */
	wm2000_anc_set_mode(wm2000);

	return 0;
}