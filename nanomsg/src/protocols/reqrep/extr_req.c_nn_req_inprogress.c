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
struct nn_req {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ NN_REQ_STATE_IDLE ; 
 scalar_t__ NN_REQ_STATE_PASSIVE ; 
 scalar_t__ NN_REQ_STATE_STOPPING ; 

int nn_req_inprogress (struct nn_req *self)
{
    /*  Return 1 if there's a request submitted. 0 otherwise. */
    return self->state == NN_REQ_STATE_IDLE ||
        self->state == NN_REQ_STATE_PASSIVE ||
        self->state == NN_REQ_STATE_STOPPING ? 0 : 1;
}