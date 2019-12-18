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
struct TYPE_2__ {int /*<<< orphan*/  tls_exit_signal; } ;
struct context {TYPE_1__ c2; } ;

/* Variables and functions */
 int /*<<< orphan*/  register_signal (struct context*,int /*<<< orphan*/ ,char*) ; 

void
check_tls_errors_nco(struct context *c)
{
    register_signal(c, c->c2.tls_exit_signal, "tls-error"); /* SOFT-SIGUSR1 -- TLS error */
}