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
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* raw_audio ) (int /*<<< orphan*/ ,struct audio_data*) ;int /*<<< orphan*/  (* raw_audio2 ) (int /*<<< orphan*/ ,size_t,struct audio_data*) ;} ;
struct obs_output {TYPE_2__ context; TYPE_1__ info; } ;
struct audio_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  data_active (struct obs_output*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,size_t,struct audio_data*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,struct audio_data*) ; 

__attribute__((used)) static void default_raw_audio_callback(void *param, size_t mix_idx,
		struct audio_data *frames)
{
	struct obs_output *output = param;
	if (!data_active(output))
		return;

	if (output->info.raw_audio2)
		output->info.raw_audio2(output->context.data, mix_idx, frames);
	else
		output->info.raw_audio(output->context.data, frames);
}