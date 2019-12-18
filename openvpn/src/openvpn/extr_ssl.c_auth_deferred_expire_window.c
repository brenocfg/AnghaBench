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
struct tls_options {int handshake_window; int renegotiate_seconds; } ;

/* Variables and functions */

__attribute__((used)) static int
auth_deferred_expire_window(const struct tls_options *o)
{
    int ret = o->handshake_window;
    const int r2 = o->renegotiate_seconds / 2;

    if (o->renegotiate_seconds && r2 < ret)
    {
        ret = r2;
    }
    return ret;
}