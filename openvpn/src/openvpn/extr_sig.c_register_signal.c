#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct context {TYPE_1__* sig; } ;
struct TYPE_2__ {int signal_received; char const* signal_text; } ;

/* Variables and functions */
 int SIGTERM ; 

void
register_signal(struct context *c, int sig, const char *text)
{
    if (c->sig->signal_received != SIGTERM)
    {
        c->sig->signal_received = sig;
    }
    c->sig->signal_text = text;
}