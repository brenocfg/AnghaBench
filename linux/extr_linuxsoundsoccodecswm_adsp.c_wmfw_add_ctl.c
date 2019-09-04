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
struct TYPE_4__ {int /*<<< orphan*/  put; int /*<<< orphan*/  get; int /*<<< orphan*/  max; } ;
struct wm_coeff_ctl {int type; TYPE_2__ bytes_ext; int /*<<< orphan*/  len; int /*<<< orphan*/  flags; scalar_t__ name; } ;
struct wm_adsp {int /*<<< orphan*/  component; } ;
struct TYPE_3__ {int /*<<< orphan*/  c; } ;
struct snd_kcontrol_new {unsigned long private_value; int access; int /*<<< orphan*/  put; int /*<<< orphan*/  get; TYPE_1__ tlv; int /*<<< orphan*/  iface; int /*<<< orphan*/  info; scalar_t__ name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_IFACE_MIXER ; 
#define  WMFW_CTL_TYPE_ACKED 128 
 int /*<<< orphan*/  kfree (struct snd_kcontrol_new*) ; 
 struct snd_kcontrol_new* kzalloc (int,int /*<<< orphan*/ ) ; 
 int snd_soc_add_component_controls (int /*<<< orphan*/ ,struct snd_kcontrol_new*,int) ; 
 int /*<<< orphan*/  snd_soc_bytes_tlv_callback ; 
 int /*<<< orphan*/  wm_coeff_get ; 
 int /*<<< orphan*/  wm_coeff_get_acked ; 
 int /*<<< orphan*/  wm_coeff_info ; 
 int /*<<< orphan*/  wm_coeff_put ; 
 int /*<<< orphan*/  wm_coeff_put_acked ; 
 int /*<<< orphan*/  wm_coeff_tlv_get ; 
 int /*<<< orphan*/  wm_coeff_tlv_put ; 
 int wmfw_convert_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wmfw_add_ctl(struct wm_adsp *dsp, struct wm_coeff_ctl *ctl)
{
	struct snd_kcontrol_new *kcontrol;
	int ret;

	if (!ctl || !ctl->name)
		return -EINVAL;

	kcontrol = kzalloc(sizeof(*kcontrol), GFP_KERNEL);
	if (!kcontrol)
		return -ENOMEM;

	kcontrol->name = ctl->name;
	kcontrol->info = wm_coeff_info;
	kcontrol->iface = SNDRV_CTL_ELEM_IFACE_MIXER;
	kcontrol->tlv.c = snd_soc_bytes_tlv_callback;
	kcontrol->private_value = (unsigned long)&ctl->bytes_ext;
	kcontrol->access = wmfw_convert_flags(ctl->flags, ctl->len);

	switch (ctl->type) {
	case WMFW_CTL_TYPE_ACKED:
		kcontrol->get = wm_coeff_get_acked;
		kcontrol->put = wm_coeff_put_acked;
		break;
	default:
		if (kcontrol->access & SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK) {
			ctl->bytes_ext.max = ctl->len;
			ctl->bytes_ext.get = wm_coeff_tlv_get;
			ctl->bytes_ext.put = wm_coeff_tlv_put;
		} else {
			kcontrol->get = wm_coeff_get;
			kcontrol->put = wm_coeff_put;
		}
		break;
	}

	ret = snd_soc_add_component_controls(dsp->component, kcontrol, 1);
	if (ret < 0)
		goto err_kcontrol;

	kfree(kcontrol);

	return 0;

err_kcontrol:
	kfree(kcontrol);
	return ret;
}