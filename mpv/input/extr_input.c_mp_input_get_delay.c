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
struct input_ctx {int dummy; } ;

/* Variables and functions */
 double INFINITY ; 
 int /*<<< orphan*/  adjust_max_wait_time (struct input_ctx*,double*) ; 
 int /*<<< orphan*/  input_lock (struct input_ctx*) ; 
 int /*<<< orphan*/  input_unlock (struct input_ctx*) ; 

double mp_input_get_delay(struct input_ctx *ictx)
{
    input_lock(ictx);
    double seconds = INFINITY;
    adjust_max_wait_time(ictx, &seconds);
    input_unlock(ictx);
    return seconds;
}