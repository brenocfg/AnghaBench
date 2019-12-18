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
struct transition_state {int /*<<< orphan*/  transitioning_audio; int /*<<< orphan*/  transitioning_video; int /*<<< orphan*/ * s; } ;
struct TYPE_3__ {int /*<<< orphan*/  transitioning_audio; int /*<<< orphan*/  transitioning_video; int /*<<< orphan*/ * transition_sources; } ;
typedef  TYPE_1__ obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_source_addref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void copy_transition_state(obs_source_t *transition,
					 struct transition_state *state)
{
	state->s[0] = transition->transition_sources[0];
	state->s[1] = transition->transition_sources[1];
	obs_source_addref(state->s[0]);
	obs_source_addref(state->s[1]);

	state->transitioning_video = transition->transitioning_video;
	state->transitioning_audio = transition->transitioning_audio;
}