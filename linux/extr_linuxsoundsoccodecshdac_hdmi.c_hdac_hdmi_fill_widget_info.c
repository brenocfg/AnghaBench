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
struct snd_soc_dapm_widget {int id; char const* sname; int num_kcontrols; int (* event ) (struct snd_soc_dapm_widget*,struct snd_kcontrol*,int) ;unsigned short event_flags; void* priv; struct snd_kcontrol_new* kcontrol_news; scalar_t__ shift; int /*<<< orphan*/  reg; int /*<<< orphan*/  name; } ;
struct snd_kcontrol_new {int dummy; } ;
struct device {int dummy; } ;
typedef  enum snd_soc_dapm_type { ____Placeholder_snd_soc_dapm_type } snd_soc_dapm_type ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SND_SOC_NOPM ; 
 int /*<<< orphan*/  devm_kstrdup (struct device*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hdac_hdmi_fill_widget_info(struct device *dev,
		struct snd_soc_dapm_widget *w, enum snd_soc_dapm_type id,
		void *priv, const char *wname, const char *stream,
		struct snd_kcontrol_new *wc, int numkc,
		int (*event)(struct snd_soc_dapm_widget *,
		struct snd_kcontrol *, int), unsigned short event_flags)
{
	w->id = id;
	w->name = devm_kstrdup(dev, wname, GFP_KERNEL);
	if (!w->name)
		return -ENOMEM;

	w->sname = stream;
	w->reg = SND_SOC_NOPM;
	w->shift = 0;
	w->kcontrol_news = wc;
	w->num_kcontrols = numkc;
	w->priv = priv;
	w->event = event;
	w->event_flags = event_flags;

	return 0;
}