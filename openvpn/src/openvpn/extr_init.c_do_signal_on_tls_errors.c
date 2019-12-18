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
struct TYPE_4__ {int /*<<< orphan*/  tls_exit_signal; } ;
struct TYPE_3__ {scalar_t__ tls_exit; } ;
struct context {TYPE_2__ c2; TYPE_1__ options; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGUSR1 ; 

__attribute__((used)) static void
do_signal_on_tls_errors(struct context *c)
{
    if (c->options.tls_exit)
    {
        c->c2.tls_exit_signal = SIGTERM;
    }
    else
    {
        c->c2.tls_exit_signal = SIGUSR1;
    }
}