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
struct stinger_info {int /*<<< orphan*/  transition_b_mul; } ;

/* Variables and functions */
 float calc_fade (float,int /*<<< orphan*/ ) ; 

__attribute__((used)) static float mix_b_fade_in_out(void *data, float t)
{
	struct stinger_info *s = data;
	return 1.0f - calc_fade(1.0f - t, s->transition_b_mul);
}