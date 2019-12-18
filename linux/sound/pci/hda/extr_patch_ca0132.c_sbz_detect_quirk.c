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
struct TYPE_2__ {int subsystem_id; } ;
struct hda_codec {TYPE_1__ core; struct ca0132_spec* spec; } ;
struct ca0132_spec {int /*<<< orphan*/  quirk; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUIRK_SBZ ; 
 int /*<<< orphan*/  QUIRK_ZXR ; 
 int /*<<< orphan*/  QUIRK_ZXR_DBPRO ; 

__attribute__((used)) static void sbz_detect_quirk(struct hda_codec *codec)
{
	struct ca0132_spec *spec = codec->spec;

	switch (codec->core.subsystem_id) {
	case 0x11020033:
		spec->quirk = QUIRK_ZXR;
		break;
	case 0x1102003f:
		spec->quirk = QUIRK_ZXR_DBPRO;
		break;
	default:
		spec->quirk = QUIRK_SBZ;
		break;
	}
}