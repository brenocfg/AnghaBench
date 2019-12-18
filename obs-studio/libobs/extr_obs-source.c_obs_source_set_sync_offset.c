#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct calldata {int dummy; } ;
typedef  int /*<<< orphan*/  stack ;
struct TYPE_6__ {int /*<<< orphan*/  signals; } ;
struct TYPE_7__ {int /*<<< orphan*/  sync_offset; TYPE_1__ context; } ;
typedef  TYPE_2__ obs_source_t ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  calldata_init_fixed (struct calldata*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  calldata_int (struct calldata*,char*) ; 
 int /*<<< orphan*/  calldata_set_int (struct calldata*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calldata_set_ptr (struct calldata*,char*,TYPE_2__*) ; 
 scalar_t__ obs_source_valid (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  signal_handler_signal (int /*<<< orphan*/ ,char*,struct calldata*) ; 

void obs_source_set_sync_offset(obs_source_t *source, int64_t offset)
{
	if (obs_source_valid(source, "obs_source_set_sync_offset")) {
		struct calldata data;
		uint8_t stack[128];

		calldata_init_fixed(&data, stack, sizeof(stack));
		calldata_set_ptr(&data, "source", source);
		calldata_set_int(&data, "offset", offset);

		signal_handler_signal(source->context.signals, "audio_sync",
				      &data);

		source->sync_offset = calldata_int(&data, "offset");
	}
}