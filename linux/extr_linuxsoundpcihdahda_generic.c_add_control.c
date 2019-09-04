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
struct snd_kcontrol_new {int index; unsigned long private_value; int /*<<< orphan*/  subdevice; } ;
struct hda_gen_spec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDA_SUBDEV_AMP_FLAG ; 
 int /*<<< orphan*/ * control_templates ; 
 scalar_t__ get_amp_nid_ (unsigned long) ; 
 struct snd_kcontrol_new* snd_hda_gen_add_kctl (struct hda_gen_spec*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct snd_kcontrol_new *
add_control(struct hda_gen_spec *spec, int type, const char *name,
		       int cidx, unsigned long val)
{
	struct snd_kcontrol_new *knew;

	knew = snd_hda_gen_add_kctl(spec, name, &control_templates[type]);
	if (!knew)
		return NULL;
	knew->index = cidx;
	if (get_amp_nid_(val))
		knew->subdevice = HDA_SUBDEV_AMP_FLAG;
	knew->private_value = val;
	return knew;
}