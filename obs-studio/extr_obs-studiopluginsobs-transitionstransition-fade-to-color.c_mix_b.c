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
struct fade_to_color_info {float switch_point; } ;

/* Variables and functions */
 float lerp (float,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smoothstep (float,float,float) ; 

__attribute__((used)) static float mix_b(void *data, float t)
{
	struct fade_to_color_info *fade_to_color = data;
	float sp = fade_to_color->switch_point;

	return lerp(0.0f, t, smoothstep(sp, 1.0f, t));
}