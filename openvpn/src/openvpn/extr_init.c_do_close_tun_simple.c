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
struct TYPE_2__ {int tuntap_owned; int /*<<< orphan*/  pulled_options_digest_save; int /*<<< orphan*/ * tuntap; } ;
struct context {TYPE_1__ c1; int /*<<< orphan*/  net_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D_CLOSE ; 
 int /*<<< orphan*/  close_tun (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
do_close_tun_simple(struct context *c)
{
    msg(D_CLOSE, "Closing TUN/TAP interface");
    if (c->c1.tuntap)
    {
        close_tun(c->c1.tuntap, &c->net_ctx);
        c->c1.tuntap = NULL;
    }
    c->c1.tuntap_owned = false;
#if P2MP
    CLEAR(c->c1.pulled_options_digest_save);
#endif
}