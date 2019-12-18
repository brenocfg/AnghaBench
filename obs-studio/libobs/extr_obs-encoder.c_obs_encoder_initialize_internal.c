#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ type; int /*<<< orphan*/  (* create ) (int /*<<< orphan*/ ,TYPE_3__*) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  data; int /*<<< orphan*/  settings; } ;
struct TYPE_11__ {int initialized; TYPE_2__ orig_info; TYPE_1__ context; TYPE_2__ info; } ;
typedef  TYPE_3__ obs_encoder_t ;

/* Variables and functions */
 scalar_t__ OBS_ENCODER_AUDIO ; 
 int can_reroute ; 
 scalar_t__ encoder_active (TYPE_3__*) ; 
 int /*<<< orphan*/  intitialize_audio_encoder (TYPE_3__*) ; 
 int /*<<< orphan*/  obs_encoder_shutdown (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static inline bool obs_encoder_initialize_internal(obs_encoder_t *encoder)
{
	if (encoder_active(encoder))
		return true;
	if (encoder->initialized)
		return true;

	obs_encoder_shutdown(encoder);

	if (encoder->orig_info.create) {
		can_reroute = true;
		encoder->info = encoder->orig_info;
		encoder->context.data = encoder->orig_info.create(
			encoder->context.settings, encoder);
		can_reroute = false;
	}
	if (!encoder->context.data)
		return false;

	if (encoder->orig_info.type == OBS_ENCODER_AUDIO)
		intitialize_audio_encoder(encoder);

	encoder->initialized = true;
	return true;
}