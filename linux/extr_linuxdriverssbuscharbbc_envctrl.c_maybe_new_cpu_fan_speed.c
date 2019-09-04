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
struct bbc_fan_control {int cpu_fan_speed; int system_fan_speed; } ;
typedef  enum fan_action { ____Placeholder_fan_action } fan_action ;

/* Variables and functions */
 int /*<<< orphan*/  FAN_CPU ; 
 int FAN_FASTER ; 
 int FAN_FULLBLAST ; 
 int FAN_SAME ; 
 int FAN_SPEED_MAX ; 
 int FAN_SPEED_MIN ; 
 int prioritize_fan_action (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int maybe_new_cpu_fan_speed(struct bbc_fan_control *fp)
{
	enum fan_action decision = prioritize_fan_action(FAN_CPU);
	int ret;

	if (decision == FAN_SAME)
		return 0;

	ret = 1;
	if (decision == FAN_FULLBLAST) {
		if (fp->cpu_fan_speed >= FAN_SPEED_MAX)
			ret = 0;
		else
			fp->cpu_fan_speed = FAN_SPEED_MAX;
	} else {
		if (decision == FAN_FASTER) {
			if (fp->cpu_fan_speed >= FAN_SPEED_MAX)
				ret = 0;
			else {
				fp->cpu_fan_speed += 2;
				if (fp->system_fan_speed <
				    (fp->cpu_fan_speed - 3))
					fp->system_fan_speed =
						fp->cpu_fan_speed - 3;
			}
		} else {
			if (fp->cpu_fan_speed <= FAN_SPEED_MIN)
				ret = 0;
			else
				fp->cpu_fan_speed -= 1;
		}
	}

	return ret;
}