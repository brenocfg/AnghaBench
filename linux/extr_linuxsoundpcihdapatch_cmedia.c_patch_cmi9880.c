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
struct hda_codec {int /*<<< orphan*/  patch_ops; struct cmi_spec* spec; } ;
struct auto_pin_cfg {int dummy; } ;
struct TYPE_2__ {struct auto_pin_cfg autocfg; } ;
struct cmi_spec {TYPE_1__ gen; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cmi_auto_patch_ops ; 
 struct cmi_spec* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_gen_free (struct hda_codec*) ; 
 int snd_hda_gen_parse_auto_config (struct hda_codec*,struct auto_pin_cfg*) ; 
 int /*<<< orphan*/  snd_hda_gen_spec_init (TYPE_1__*) ; 
 int snd_hda_parse_pin_defcfg (struct hda_codec*,struct auto_pin_cfg*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int patch_cmi9880(struct hda_codec *codec)
{
	struct cmi_spec *spec;
	struct auto_pin_cfg *cfg;
	int err;

	spec = kzalloc(sizeof(*spec), GFP_KERNEL);
	if (spec == NULL)
		return -ENOMEM;

	codec->spec = spec;
	codec->patch_ops = cmi_auto_patch_ops;
	cfg = &spec->gen.autocfg;
	snd_hda_gen_spec_init(&spec->gen);

	err = snd_hda_parse_pin_defcfg(codec, cfg, NULL, 0);
	if (err < 0)
		goto error;
	err = snd_hda_gen_parse_auto_config(codec, cfg);
	if (err < 0)
		goto error;

	return 0;

 error:
	snd_hda_gen_free(codec);
	return err;
}