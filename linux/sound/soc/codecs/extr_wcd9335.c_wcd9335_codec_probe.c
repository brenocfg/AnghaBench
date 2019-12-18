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
struct wcd9335_codec {TYPE_1__* dai; struct snd_soc_component* component; int /*<<< orphan*/  hph_mode; int /*<<< orphan*/  clsh_ctrl; int /*<<< orphan*/  version; int /*<<< orphan*/  regmap; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  slim_ch_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLS_H_HIFI ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int NUM_CODEC_DAIS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct wcd9335_codec* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_init_regmap (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcd9335_codec_init (struct snd_soc_component*) ; 
 int wcd9335_setup_irqs (struct wcd9335_codec*) ; 
 int /*<<< orphan*/  wcd_clsh_ctrl_alloc (struct snd_soc_component*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wcd9335_codec_probe(struct snd_soc_component *component)
{
	struct wcd9335_codec *wcd = dev_get_drvdata(component->dev);
	int i;

	snd_soc_component_init_regmap(component, wcd->regmap);
	/* Class-H Init*/
	wcd->clsh_ctrl = wcd_clsh_ctrl_alloc(component, wcd->version);
	if (IS_ERR(wcd->clsh_ctrl))
		return PTR_ERR(wcd->clsh_ctrl);

	/* Default HPH Mode to Class-H HiFi */
	wcd->hph_mode = CLS_H_HIFI;
	wcd->component = component;

	wcd9335_codec_init(component);

	for (i = 0; i < NUM_CODEC_DAIS; i++)
		INIT_LIST_HEAD(&wcd->dai[i].slim_ch_list);

	return wcd9335_setup_irqs(wcd);
}