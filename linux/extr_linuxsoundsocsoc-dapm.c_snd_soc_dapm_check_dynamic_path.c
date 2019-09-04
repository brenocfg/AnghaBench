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
struct snd_soc_dapm_widget {int id; int /*<<< orphan*/  name; } ;
struct snd_soc_dapm_context {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
#define  snd_soc_dapm_demux 132 
#define  snd_soc_dapm_mixer 131 
#define  snd_soc_dapm_mixer_named_ctl 130 
#define  snd_soc_dapm_mux 129 
#define  snd_soc_dapm_switch 128 

__attribute__((used)) static int snd_soc_dapm_check_dynamic_path(struct snd_soc_dapm_context *dapm,
	struct snd_soc_dapm_widget *source, struct snd_soc_dapm_widget *sink,
	const char *control)
{
	bool dynamic_source = false;
	bool dynamic_sink = false;

	if (!control)
		return 0;

	switch (source->id) {
	case snd_soc_dapm_demux:
		dynamic_source = true;
		break;
	default:
		break;
	}

	switch (sink->id) {
	case snd_soc_dapm_mux:
	case snd_soc_dapm_switch:
	case snd_soc_dapm_mixer:
	case snd_soc_dapm_mixer_named_ctl:
		dynamic_sink = true;
		break;
	default:
		break;
	}

	if (dynamic_source && dynamic_sink) {
		dev_err(dapm->dev,
			"Direct connection between demux and mixer/mux not supported for path %s -> [%s] -> %s\n",
			source->name, control, sink->name);
		return -EINVAL;
	} else if (!dynamic_source && !dynamic_sink) {
		dev_err(dapm->dev,
			"Control not supported for path %s -> [%s] -> %s\n",
			source->name, control, sink->name);
		return -EINVAL;
	}

	return 0;
}