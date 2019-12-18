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
struct mp_user_filter {int /*<<< orphan*/  f; } ;
struct mp_filter_command {double speed; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_FILTER_COMMAND_SET_SPEED ; 
 int /*<<< orphan*/  MP_FILTER_COMMAND_SET_SPEED_RESAMPLE ; 
 int /*<<< orphan*/  assert (double) ; 
 scalar_t__ mp_filter_command (int /*<<< orphan*/ ,struct mp_filter_command*) ; 

__attribute__((used)) static void set_speed_any(struct mp_user_filter **filters, int num_filters,
                          bool resample, double *speed)
{
    for (int n = num_filters - 1; n >= 0; n--) {
        assert(*speed);
        struct mp_filter_command cmd = {
            .type = resample ? MP_FILTER_COMMAND_SET_SPEED_RESAMPLE
                             : MP_FILTER_COMMAND_SET_SPEED,
            .speed = *speed,
        };
        if (mp_filter_command(filters[n]->f, &cmd))
            *speed = 1.0;
    }
}