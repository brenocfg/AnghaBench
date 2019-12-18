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
 int /*<<< orphan*/  input_lock (struct input_ctx*) ; 
 int /*<<< orphan*/  input_unlock (struct input_ctx*) ; 
 int /*<<< orphan*/  mp_input_feed_key (struct input_ctx*,int,double,int) ; 

void mp_input_put_wheel(struct input_ctx *ictx, int direction, double value)
{
    if (value == 0.0)
        return;
    input_lock(ictx);
    mp_input_feed_key(ictx, direction, value, false);
    input_unlock(ictx);
}