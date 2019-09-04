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
typedef  int /*<<< orphan*/  uint32_t ;
struct obs_source_info {int /*<<< orphan*/  output_flags; } ;

/* Variables and functions */
 struct obs_source_info* get_source_info (char const*) ; 

uint32_t obs_get_source_output_flags(const char *id)
{
	const struct obs_source_info *info = get_source_info(id);
	return info ? info->output_flags : 0;
}