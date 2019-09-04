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
struct TYPE_3__ {int /*<<< orphan*/  chmap_validate; int /*<<< orphan*/  chmap_cea_alloc_validate_get_type; } ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct hdmi_spec {int dyn_pin_out; TYPE_2__ chmap; } ;
struct hda_codec {struct hdmi_spec* spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvhdmi_chmap_cea_alloc_validate_get_type ; 
 int /*<<< orphan*/  nvhdmi_chmap_validate ; 
 int patch_generic_hdmi (struct hda_codec*) ; 

__attribute__((used)) static int patch_nvhdmi(struct hda_codec *codec)
{
	struct hdmi_spec *spec;
	int err;

	err = patch_generic_hdmi(codec);
	if (err)
		return err;

	spec = codec->spec;
	spec->dyn_pin_out = true;

	spec->chmap.ops.chmap_cea_alloc_validate_get_type =
		nvhdmi_chmap_cea_alloc_validate_get_type;
	spec->chmap.ops.chmap_validate = nvhdmi_chmap_validate;

	return 0;
}