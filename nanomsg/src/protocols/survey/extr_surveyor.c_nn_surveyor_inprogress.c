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
struct nn_surveyor {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ NN_SURVEYOR_STATE_IDLE ; 
 scalar_t__ NN_SURVEYOR_STATE_PASSIVE ; 
 scalar_t__ NN_SURVEYOR_STATE_STOPPING ; 

__attribute__((used)) static int nn_surveyor_inprogress (struct nn_surveyor *self)
{
    /*  Return 1 if there's a survey going on. 0 otherwise. */
    return self->state == NN_SURVEYOR_STATE_IDLE ||
        self->state == NN_SURVEYOR_STATE_PASSIVE ||
        self->state == NN_SURVEYOR_STATE_STOPPING ? 0 : 1;
}