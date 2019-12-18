#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct calldata {int dummy; } ;
typedef  int /*<<< orphan*/  stack ;
struct TYPE_7__ {int /*<<< orphan*/  signals; } ;
struct TYPE_8__ {int output_flags; } ;
struct TYPE_9__ {scalar_t__ audio_mixers; TYPE_1__ context; TYPE_2__ info; } ;
typedef  TYPE_3__ obs_source_t ;

/* Variables and functions */
 int OBS_SOURCE_AUDIO ; 
 int /*<<< orphan*/  calldata_init_fixed (struct calldata*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ calldata_int (struct calldata*,char*) ; 
 int /*<<< orphan*/  calldata_set_int (struct calldata*,char*,scalar_t__) ; 
 int /*<<< orphan*/  calldata_set_ptr (struct calldata*,char*,TYPE_3__*) ; 
 int /*<<< orphan*/  obs_source_valid (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  signal_handler_signal (int /*<<< orphan*/ ,char*,struct calldata*) ; 

void obs_source_set_audio_mixers(obs_source_t *source, uint32_t mixers)
{
	struct calldata data;
	uint8_t stack[128];

	if (!obs_source_valid(source, "obs_source_set_audio_mixers"))
		return;
	if ((source->info.output_flags & OBS_SOURCE_AUDIO) == 0)
		return;

	if (source->audio_mixers == mixers)
		return;

	calldata_init_fixed(&data, stack, sizeof(stack));
	calldata_set_ptr(&data, "source", source);
	calldata_set_int(&data, "mixers", mixers);

	signal_handler_signal(source->context.signals, "audio_mixers", &data);

	mixers = (uint32_t)calldata_int(&data, "mixers");

	source->audio_mixers = mixers;
}