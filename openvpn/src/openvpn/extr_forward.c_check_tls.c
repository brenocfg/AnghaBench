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
struct TYPE_2__ {scalar_t__ tls_multi; } ;
struct context {TYPE_1__ c2; } ;

/* Variables and functions */

__attribute__((used)) static inline void
check_tls(struct context *c)
{
    void check_tls_dowork(struct context *c);

    if (c->c2.tls_multi)
    {
        check_tls_dowork(c);
    }
}