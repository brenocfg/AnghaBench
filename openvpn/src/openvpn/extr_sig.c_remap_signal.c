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
struct TYPE_4__ {scalar_t__ remap_sigusr1; } ;
struct context {TYPE_2__ options; TYPE_1__* sig; } ;
struct TYPE_3__ {scalar_t__ signal_received; } ;

/* Variables and functions */
 scalar_t__ SIGUSR1 ; 

void
remap_signal(struct context *c)
{
    if (c->sig->signal_received == SIGUSR1 && c->options.remap_sigusr1)
    {
        c->sig->signal_received = c->options.remap_sigusr1;
    }
}