#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dapm_path {TYPE_1__* sink; int /*<<< orphan*/  name; } ;
struct snd_soc_dapm_context {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int num_kcontrols; TYPE_2__* kcontrol_news; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dapm_set_mixer_path_status (struct snd_soc_dapm_path*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dapm_connect_mixer(struct snd_soc_dapm_context *dapm,
	struct snd_soc_dapm_path *path, const char *control_name)
{
	int i, nth_path = 0;

	/* search for mixer kcontrol */
	for (i = 0; i < path->sink->num_kcontrols; i++) {
		if (!strcmp(control_name, path->sink->kcontrol_news[i].name)) {
			path->name = path->sink->kcontrol_news[i].name;
			dapm_set_mixer_path_status(path, i, nth_path++);
			return 0;
		}
	}
	return -ENODEV;
}