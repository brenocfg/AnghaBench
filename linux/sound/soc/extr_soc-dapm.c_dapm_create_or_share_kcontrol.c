#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dapm_widget {int id; char* name; struct snd_kcontrol** kcontrols; TYPE_2__* kcontrol_news; struct snd_soc_dapm_context* dapm; } ;
struct snd_soc_dapm_context {int /*<<< orphan*/  dev; TYPE_1__* card; } ;
struct snd_kcontrol {int /*<<< orphan*/  private_free; } ;
struct snd_card {int dummy; } ;
struct TYPE_5__ {char* name; } ;
struct TYPE_4__ {struct snd_card* snd_card; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int dapm_is_shared_kcontrol (struct snd_soc_dapm_context*,struct snd_soc_dapm_widget*,TYPE_2__*,struct snd_kcontrol**) ; 
 int dapm_kcontrol_add_widget (struct snd_kcontrol*,struct snd_soc_dapm_widget*) ; 
 int dapm_kcontrol_data_alloc (struct snd_soc_dapm_widget*,struct snd_kcontrol*,char const*) ; 
 int /*<<< orphan*/  dapm_kcontrol_free ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char*,char const*,int) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int snd_ctl_add (struct snd_card*,struct snd_kcontrol*) ; 
 int /*<<< orphan*/  snd_ctl_free_one (struct snd_kcontrol*) ; 
 struct snd_kcontrol* snd_soc_cnew (TYPE_2__*,int /*<<< orphan*/ *,char const*,char const*) ; 
#define  snd_soc_dapm_demux 135 
#define  snd_soc_dapm_effect 134 
#define  snd_soc_dapm_mixer 133 
#define  snd_soc_dapm_mixer_named_ctl 132 
#define  snd_soc_dapm_mux 131 
#define  snd_soc_dapm_out_drv 130 
#define  snd_soc_dapm_pga 129 
#define  snd_soc_dapm_switch 128 
 char* soc_dapm_prefix (struct snd_soc_dapm_context*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int dapm_create_or_share_kcontrol(struct snd_soc_dapm_widget *w,
	int kci)
{
	struct snd_soc_dapm_context *dapm = w->dapm;
	struct snd_card *card = dapm->card->snd_card;
	const char *prefix;
	size_t prefix_len;
	int shared;
	struct snd_kcontrol *kcontrol;
	bool wname_in_long_name, kcname_in_long_name;
	char *long_name = NULL;
	const char *name;
	int ret = 0;

	prefix = soc_dapm_prefix(dapm);
	if (prefix)
		prefix_len = strlen(prefix) + 1;
	else
		prefix_len = 0;

	shared = dapm_is_shared_kcontrol(dapm, w, &w->kcontrol_news[kci],
					 &kcontrol);

	if (!kcontrol) {
		if (shared) {
			wname_in_long_name = false;
			kcname_in_long_name = true;
		} else {
			switch (w->id) {
			case snd_soc_dapm_switch:
			case snd_soc_dapm_mixer:
			case snd_soc_dapm_pga:
			case snd_soc_dapm_effect:
			case snd_soc_dapm_out_drv:
				wname_in_long_name = true;
				kcname_in_long_name = true;
				break;
			case snd_soc_dapm_mixer_named_ctl:
				wname_in_long_name = false;
				kcname_in_long_name = true;
				break;
			case snd_soc_dapm_demux:
			case snd_soc_dapm_mux:
				wname_in_long_name = true;
				kcname_in_long_name = false;
				break;
			default:
				return -EINVAL;
			}
		}

		if (wname_in_long_name && kcname_in_long_name) {
			/*
			 * The control will get a prefix from the control
			 * creation process but we're also using the same
			 * prefix for widgets so cut the prefix off the
			 * front of the widget name.
			 */
			long_name = kasprintf(GFP_KERNEL, "%s %s",
				 w->name + prefix_len,
				 w->kcontrol_news[kci].name);
			if (long_name == NULL)
				return -ENOMEM;

			name = long_name;
		} else if (wname_in_long_name) {
			long_name = NULL;
			name = w->name + prefix_len;
		} else {
			long_name = NULL;
			name = w->kcontrol_news[kci].name;
		}

		kcontrol = snd_soc_cnew(&w->kcontrol_news[kci], NULL, name,
					prefix);
		if (!kcontrol) {
			ret = -ENOMEM;
			goto exit_free;
		}

		kcontrol->private_free = dapm_kcontrol_free;

		ret = dapm_kcontrol_data_alloc(w, kcontrol, name);
		if (ret) {
			snd_ctl_free_one(kcontrol);
			goto exit_free;
		}

		ret = snd_ctl_add(card, kcontrol);
		if (ret < 0) {
			dev_err(dapm->dev,
				"ASoC: failed to add widget %s dapm kcontrol %s: %d\n",
				w->name, name, ret);
			goto exit_free;
		}
	}

	ret = dapm_kcontrol_add_widget(kcontrol, w);
	if (ret == 0)
		w->kcontrols[kci] = kcontrol;

exit_free:
	kfree(long_name);

	return ret;
}