#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  remote_list; int /*<<< orphan*/  bind_local; } ;
struct TYPE_10__ {int tuntap_owned; TYPE_5__* tuntap; TYPE_1__ link_socket_addr; } ;
struct TYPE_9__ {int /*<<< orphan*/  tuntap_options; int /*<<< orphan*/  wintun; int /*<<< orphan*/  ifconfig_nowarn; int /*<<< orphan*/  ifconfig_ipv6_remote; int /*<<< orphan*/  ifconfig_ipv6_netbits; int /*<<< orphan*/  ifconfig_ipv6_local; int /*<<< orphan*/  ifconfig_remote_netmask; int /*<<< orphan*/  ifconfig_local; int /*<<< orphan*/  topology; int /*<<< orphan*/  dev_type; int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  frame; int /*<<< orphan*/  es; } ;
struct context {TYPE_4__ c1; TYPE_3__ options; TYPE_2__ c2; int /*<<< orphan*/  net_ctx; } ;
struct TYPE_11__ {int /*<<< orphan*/  wintun; } ;

/* Variables and functions */
 TYPE_5__* init_tun (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_tun_post (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
do_init_tun(struct context *c)
{
    c->c1.tuntap = init_tun(c->options.dev,
                            c->options.dev_type,
                            c->options.topology,
                            c->options.ifconfig_local,
                            c->options.ifconfig_remote_netmask,
                            c->options.ifconfig_ipv6_local,
                            c->options.ifconfig_ipv6_netbits,
                            c->options.ifconfig_ipv6_remote,
                            c->c1.link_socket_addr.bind_local,
                            c->c1.link_socket_addr.remote_list,
                            !c->options.ifconfig_nowarn,
                            c->c2.es,
                            &c->net_ctx);

#ifdef _WIN32
    c->c1.tuntap->wintun = c->options.wintun;
#endif

    init_tun_post(c->c1.tuntap,
                  &c->c2.frame,
                  &c->options.tuntap_options);

    c->c1.tuntap_owned = true;
}