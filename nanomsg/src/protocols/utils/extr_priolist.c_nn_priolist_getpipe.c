#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nn_priolist {int current; TYPE_2__* slots; } ;
struct nn_pipe {int dummy; } ;
struct TYPE_4__ {TYPE_1__* current; } ;
struct TYPE_3__ {struct nn_pipe* pipe; } ;

/* Variables and functions */
 scalar_t__ nn_slow (int) ; 

struct nn_pipe *nn_priolist_getpipe (struct nn_priolist *self)
{
    if (nn_slow (self->current == -1))
        return NULL;
    return self->slots [self->current - 1].current->pipe;
}