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

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (void*) ; 
 float cubic_ease_in_out (float) ; 

__attribute__((used)) static float mix_b(void *data, float t)
{
	UNUSED_PARAMETER(data);
	return cubic_ease_in_out(t);
}