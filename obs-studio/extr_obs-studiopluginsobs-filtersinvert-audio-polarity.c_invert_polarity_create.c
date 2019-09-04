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
typedef  void obs_source_t ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *invert_polarity_create(obs_data_t *settings, obs_source_t *filter)
{
	UNUSED_PARAMETER(settings);
	return filter;
}