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
struct hdmi_spec_per_pin {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* pin_cvt_fixup ) (struct hda_codec*,struct hdmi_spec_per_pin*,int /*<<< orphan*/ ) ;} ;
struct hdmi_spec {TYPE_1__ ops; } ;
struct hda_codec {struct hdmi_spec* spec; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct hda_codec*,struct hdmi_spec_per_pin*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pin_cvt_fixup(struct hda_codec *codec,
			  struct hdmi_spec_per_pin *per_pin,
			  hda_nid_t cvt_nid)
{
	struct hdmi_spec *spec = codec->spec;

	if (spec->ops.pin_cvt_fixup)
		spec->ops.pin_cvt_fixup(codec, per_pin, cvt_nid);
}