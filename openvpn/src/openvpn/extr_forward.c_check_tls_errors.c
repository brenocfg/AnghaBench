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
struct TYPE_4__ {TYPE_1__* tls_multi; int /*<<< orphan*/  link_socket; scalar_t__ tls_exit_signal; } ;
struct context {TYPE_2__ c2; } ;
struct TYPE_3__ {scalar_t__ n_hard_errors; scalar_t__ n_soft_errors; } ;

/* Variables and functions */
 scalar_t__ link_socket_connection_oriented (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
check_tls_errors(struct context *c)
{
    void check_tls_errors_co(struct context *c);

    void check_tls_errors_nco(struct context *c);

    if (c->c2.tls_multi && c->c2.tls_exit_signal)
    {
        if (link_socket_connection_oriented(c->c2.link_socket))
        {
            if (c->c2.tls_multi->n_soft_errors)
            {
                check_tls_errors_co(c);
            }
        }
        else
        {
            if (c->c2.tls_multi->n_hard_errors)
            {
                check_tls_errors_nco(c);
            }
        }
    }
}