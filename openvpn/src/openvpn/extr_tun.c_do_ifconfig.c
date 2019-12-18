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
struct tuntap {scalar_t__ did_ifconfig_ipv6_setup; scalar_t__ did_ifconfig_setup; int /*<<< orphan*/  local_ipv6; int /*<<< orphan*/  local; } ;
struct env_set {int dummy; } ;
typedef  int /*<<< orphan*/  openvpn_net_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  D_LOW ; 
 int /*<<< orphan*/  OPENVPN_STATE_ASSIGN_IP ; 
 int /*<<< orphan*/  do_ifconfig_ipv4 (struct tuntap*,char const*,int,struct env_set const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_ifconfig_ipv6 (struct tuntap*,char const*,int,struct env_set const*,int /*<<< orphan*/ *) ; 
 scalar_t__ management ; 
 int /*<<< orphan*/  management_set_state (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  net_ctx_free (int /*<<< orphan*/ *) ; 

void
do_ifconfig(struct tuntap *tt, const char *ifname, int tun_mtu,
            const struct env_set *es, openvpn_net_ctx_t *ctx)
{
    msg(D_LOW, "do_ifconfig, ipv4=%d, ipv6=%d", tt->did_ifconfig_setup,
        tt->did_ifconfig_ipv6_setup);

#ifdef ENABLE_MANAGEMENT
    if (management)
    {
        management_set_state(management,
                             OPENVPN_STATE_ASSIGN_IP,
                             NULL,
                             &tt->local,
                             &tt->local_ipv6,
                             NULL,
                             NULL);
    }
#endif

    if (tt->did_ifconfig_setup)
    {
        do_ifconfig_ipv4(tt, ifname, tun_mtu, es, ctx);
    }

    if (tt->did_ifconfig_ipv6_setup)
    {
        do_ifconfig_ipv6(tt, ifname, tun_mtu, es, ctx);
    }

    /* release resources potentially allocated during interface setup */
    net_ctx_free(ctx);
}