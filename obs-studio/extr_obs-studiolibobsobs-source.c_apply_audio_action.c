#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct audio_action {int type; int /*<<< orphan*/  set; int /*<<< orphan*/  vol; } ;
struct TYPE_3__ {int /*<<< orphan*/  push_to_mute_pressed; int /*<<< orphan*/  push_to_talk_pressed; int /*<<< orphan*/  muted; int /*<<< orphan*/  volume; } ;
typedef  TYPE_1__ obs_source_t ;

/* Variables and functions */
#define  AUDIO_ACTION_MUTE 131 
#define  AUDIO_ACTION_PTM 130 
#define  AUDIO_ACTION_PTT 129 
#define  AUDIO_ACTION_VOL 128 

__attribute__((used)) static inline void apply_audio_action(obs_source_t *source,
		const struct audio_action *action)
{
	switch (action->type) {
	case AUDIO_ACTION_VOL:
		source->volume = action->vol; break;
	case AUDIO_ACTION_MUTE:
		source->muted = action->set; break;
	case AUDIO_ACTION_PTT:
		source->push_to_talk_pressed = action->set; break;
	case AUDIO_ACTION_PTM:
		source->push_to_mute_pressed = action->set; break;
	}
}