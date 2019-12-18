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
typedef  int /*<<< orphan*/  obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  data_valid (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  get_base_width (int /*<<< orphan*/ *) ; 

uint32_t obs_source_get_base_width(obs_source_t *source)
{
	if (!data_valid(source, "obs_source_get_base_width"))
		return 0;

	return get_base_width(source);
}