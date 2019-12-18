#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ event; } ;
struct TYPE_6__ {TYPE_1__ power_state; } ;
struct TYPE_7__ {TYPE_2__ power; } ;
struct TYPE_8__ {TYPE_3__ dev; } ;
struct hda_codec {TYPE_4__ core; struct alc_spec* spec; } ;
struct alc_spec {int done_hp_init; } ;

/* Variables and functions */
 scalar_t__ PM_EVENT_RESTORE ; 
 int /*<<< orphan*/  alc294_hp_init (struct hda_codec*) ; 
 int /*<<< orphan*/  alc_default_init (struct hda_codec*) ; 

__attribute__((used)) static void alc294_init(struct hda_codec *codec)
{
	struct alc_spec *spec = codec->spec;

	/* required only at boot or S4 resume time */
	if (!spec->done_hp_init ||
	    codec->core.dev.power.power_state.event == PM_EVENT_RESTORE) {
		alc294_hp_init(codec);
		spec->done_hp_init = true;
	}
	alc_default_init(codec);
}