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
struct hda_fixup {int dummy; } ;
struct hda_codec {struct alc_spec* spec; } ;
struct TYPE_2__ {int fixup; int /*<<< orphan*/  sku_cfg; } ;
struct alc_spec {TYPE_1__ cdefine; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALC_FIXUP_SKU_IGNORE ; 
 int HDA_FIXUP_ACT_PRE_PROBE ; 

__attribute__((used)) static void alc_fixup_sku_ignore(struct hda_codec *codec,
				 const struct hda_fixup *fix, int action)
{
	struct alc_spec *spec = codec->spec;
	if (action == HDA_FIXUP_ACT_PRE_PROBE) {
		spec->cdefine.fixup = 1;
		spec->cdefine.sku_cfg = ALC_FIXUP_SKU_IGNORE;
	}
}