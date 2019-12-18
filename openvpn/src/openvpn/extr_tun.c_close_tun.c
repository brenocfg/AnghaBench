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
struct tuntap {int dummy; } ;
typedef  int /*<<< orphan*/  openvpn_net_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct tuntap*) ; 
 int /*<<< orphan*/  close_tun_generic (struct tuntap*) ; 
 int /*<<< orphan*/  free (struct tuntap*) ; 

void
close_tun(struct tuntap *tt, openvpn_net_ctx_t *ctx)
{
    ASSERT(tt);

    close_tun_generic(tt);
    free(tt);
}