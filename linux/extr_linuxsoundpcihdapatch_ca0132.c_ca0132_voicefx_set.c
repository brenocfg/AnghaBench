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
struct hda_codec {struct ca0132_spec* spec; } ;
struct ca0132_spec {scalar_t__* effects_switch; } ;
struct TYPE_2__ {int /*<<< orphan*/ * reqs; int /*<<< orphan*/  mid; } ;

/* Variables and functions */
 size_t CRYSTAL_VOICE ; 
 size_t EFFECT_START_NID ; 
 unsigned int FLOAT_ONE ; 
 unsigned int FLOAT_ZERO ; 
 TYPE_1__ ca0132_voicefx ; 
 int /*<<< orphan*/  dspio_set_uint_param (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int ca0132_voicefx_set(struct hda_codec *codec, int enable)
{
	struct ca0132_spec *spec = codec->spec;
	unsigned int tmp;

	/* based on CrystalVoice state to enable VoiceFX. */
	if (enable) {
		tmp = spec->effects_switch[CRYSTAL_VOICE - EFFECT_START_NID] ?
			FLOAT_ONE : FLOAT_ZERO;
	} else {
		tmp = FLOAT_ZERO;
	}

	dspio_set_uint_param(codec, ca0132_voicefx.mid,
			     ca0132_voicefx.reqs[0], tmp);

	return 1;
}