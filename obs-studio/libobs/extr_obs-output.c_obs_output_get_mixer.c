#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  obs_output_t ;

/* Variables and functions */
 size_t get_first_mixer (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  obs_output_valid (int /*<<< orphan*/  const*,char*) ; 

size_t obs_output_get_mixer(const obs_output_t *output)
{
	if (!obs_output_valid(output, "obs_output_get_mixer"))
		return 0;

	return get_first_mixer(output);
}