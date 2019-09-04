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
typedef  int /*<<< orphan*/  obs_properties_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (void*) ; 
 int /*<<< orphan*/ * pulse_properties (int) ; 

__attribute__((used)) static obs_properties_t *pulse_input_properties(void *unused)
{
	UNUSED_PARAMETER(unused);

	return pulse_properties(true);
}