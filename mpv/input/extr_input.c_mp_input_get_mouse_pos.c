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
struct input_ctx {int mouse_x; int mouse_y; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_lock (struct input_ctx*) ; 
 int /*<<< orphan*/  input_unlock (struct input_ctx*) ; 

void mp_input_get_mouse_pos(struct input_ctx *ictx, int *x, int *y)
{
    input_lock(ictx);
    *x = ictx->mouse_x;
    *y = ictx->mouse_y;
    input_unlock(ictx);
}