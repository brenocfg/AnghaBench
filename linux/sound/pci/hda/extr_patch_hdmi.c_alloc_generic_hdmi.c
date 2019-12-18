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
struct TYPE_3__ {int /*<<< orphan*/  get_spk_alloc; int /*<<< orphan*/  is_pcm_attached; int /*<<< orphan*/  set_chmap; int /*<<< orphan*/  get_chmap; } ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct hdmi_spec {int dev_num; TYPE_2__ chmap; int /*<<< orphan*/  bind_lock; int /*<<< orphan*/  pcm_lock; int /*<<< orphan*/  ops; struct hda_codec* codec; } ;
struct hda_codec {int /*<<< orphan*/  patch_ops; struct hdmi_spec* spec; int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  generic_hdmi_patch_ops ; 
 int /*<<< orphan*/  generic_standard_hdmi_ops ; 
 int /*<<< orphan*/  hdmi_array_init (struct hdmi_spec*,int) ; 
 int /*<<< orphan*/  hdmi_get_chmap ; 
 int /*<<< orphan*/  hdmi_get_spk_alloc ; 
 int /*<<< orphan*/  hdmi_set_chmap ; 
 int /*<<< orphan*/  is_hdmi_pcm_attached ; 
 struct hdmi_spec* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_hdac_register_chmap_ops (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static int alloc_generic_hdmi(struct hda_codec *codec)
{
	struct hdmi_spec *spec;

	spec = kzalloc(sizeof(*spec), GFP_KERNEL);
	if (!spec)
		return -ENOMEM;

	spec->codec = codec;
	spec->ops = generic_standard_hdmi_ops;
	spec->dev_num = 1;	/* initialize to 1 */
	mutex_init(&spec->pcm_lock);
	mutex_init(&spec->bind_lock);
	snd_hdac_register_chmap_ops(&codec->core, &spec->chmap);

	spec->chmap.ops.get_chmap = hdmi_get_chmap;
	spec->chmap.ops.set_chmap = hdmi_set_chmap;
	spec->chmap.ops.is_pcm_attached = is_hdmi_pcm_attached;
	spec->chmap.ops.get_spk_alloc = hdmi_get_spk_alloc,

	codec->spec = spec;
	hdmi_array_init(spec, 4);

	codec->patch_ops = generic_hdmi_patch_ops;

	return 0;
}