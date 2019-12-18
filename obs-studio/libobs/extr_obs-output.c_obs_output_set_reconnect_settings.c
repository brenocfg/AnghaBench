#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int reconnect_retry_max; int reconnect_retry_sec; } ;
typedef  TYPE_1__ obs_output_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_output_valid (TYPE_1__*,char*) ; 

void obs_output_set_reconnect_settings(obs_output_t *output, int retry_count,
				       int retry_sec)
{
	if (!obs_output_valid(output, "obs_output_set_reconnect_settings"))
		return;

	output->reconnect_retry_max = retry_count;
	output->reconnect_retry_sec = retry_sec;
}