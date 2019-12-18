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
struct TYPE_4__ {char const* last_error_message; } ;
typedef  TYPE_1__ obs_output_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_output_valid (TYPE_1__*,char*) ; 

const char *obs_output_get_last_error(obs_output_t *output)
{
	if (!obs_output_valid(output, "obs_output_get_last_error"))
		return NULL;

	return output->last_error_message;
}