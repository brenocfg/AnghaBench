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
struct soc_enum {scalar_t__ reg; unsigned int shift_l; unsigned int mask; int /*<<< orphan*/ * texts; int /*<<< orphan*/  items; } ;
struct snd_soc_dapm_widget {struct snd_kcontrol_new* kcontrol_news; } ;
struct snd_soc_dapm_path {int connect; int /*<<< orphan*/  name; } ;
struct snd_soc_dapm_context {int dummy; } ;
struct snd_kcontrol_new {scalar_t__ private_value; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ SND_SOC_NOPM ; 
 int match_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 unsigned int snd_soc_enum_val_to_item (struct soc_enum*,unsigned int) ; 
 int /*<<< orphan*/  soc_dapm_read (struct snd_soc_dapm_context*,scalar_t__,unsigned int*) ; 

__attribute__((used)) static int dapm_connect_mux(struct snd_soc_dapm_context *dapm,
	struct snd_soc_dapm_path *path, const char *control_name,
	struct snd_soc_dapm_widget *w)
{
	const struct snd_kcontrol_new *kcontrol = &w->kcontrol_news[0];
	struct soc_enum *e = (struct soc_enum *)kcontrol->private_value;
	unsigned int val, item;
	int i;

	if (e->reg != SND_SOC_NOPM) {
		soc_dapm_read(dapm, e->reg, &val);
		val = (val >> e->shift_l) & e->mask;
		item = snd_soc_enum_val_to_item(e, val);
	} else {
		/* since a virtual mux has no backing registers to
		 * decide which path to connect, it will try to match
		 * with the first enumeration.  This is to ensure
		 * that the default mux choice (the first) will be
		 * correctly powered up during initialization.
		 */
		item = 0;
	}

	i = match_string(e->texts, e->items, control_name);
	if (i < 0)
		return -ENODEV;

	path->name = e->texts[i];
	path->connect = (i == item);
	return 0;

}