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
struct sock {int dummy; } ;
struct TYPE_3__ {int sysctl_tcp_recovery; } ;
struct TYPE_4__ {TYPE_1__ ipv4; } ;

/* Variables and functions */
 int TCP_RACK_LOSS_DETECTION ; 
 TYPE_2__* sock_net (struct sock const*) ; 

__attribute__((used)) static bool tcp_is_rack(const struct sock *sk)
{
	return sock_net(sk)->ipv4.sysctl_tcp_recovery & TCP_RACK_LOSS_DETECTION;
}