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
struct calldata {int /*<<< orphan*/  member_0; } ;
struct TYPE_3__ {float user_volume; } ;
struct TYPE_4__ {TYPE_1__ audio; int /*<<< orphan*/  signals; } ;

/* Variables and functions */
 scalar_t__ calldata_float (struct calldata*,char*) ; 
 int /*<<< orphan*/  calldata_free (struct calldata*) ; 
 int /*<<< orphan*/  calldata_set_float (struct calldata*,char*,float) ; 
 TYPE_2__* obs ; 
 int /*<<< orphan*/  signal_handler_signal (int /*<<< orphan*/ ,char*,struct calldata*) ; 

void obs_set_master_volume(float volume)
{
	struct calldata data = {0};

	if (!obs)
		return;

	calldata_set_float(&data, "volume", volume);
	signal_handler_signal(obs->signals, "master_volume", &data);
	volume = (float)calldata_float(&data, "volume");
	calldata_free(&data);

	obs->audio.user_volume = volume;
}