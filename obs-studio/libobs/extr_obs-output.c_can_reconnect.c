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
struct TYPE_4__ {scalar_t__ reconnect_retry_max; } ;
typedef  TYPE_1__ obs_output_t ;

/* Variables and functions */
 int OBS_OUTPUT_DISCONNECTED ; 
 int OBS_OUTPUT_SUCCESS ; 
 scalar_t__ reconnecting (TYPE_1__ const*) ; 

__attribute__((used)) static inline bool can_reconnect(const obs_output_t *output, int code)
{
	bool reconnect_active = output->reconnect_retry_max != 0;

	return (reconnecting(output) && code != OBS_OUTPUT_SUCCESS) ||
	       (reconnect_active && code == OBS_OUTPUT_DISCONNECTED);
}