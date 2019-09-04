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
struct tcp_info {int /*<<< orphan*/  tcpi_rcv_rtt; int /*<<< orphan*/  tcpi_options; int /*<<< orphan*/  tcpi_ca_state; } ;
struct sock {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_rtt; int /*<<< orphan*/  rx_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCPI_OPT_TIMESTAMPS ; 
 TYPE_1__* ccid3_hc_rx_sk (struct sock*) ; 

__attribute__((used)) static void ccid3_hc_rx_get_info(struct sock *sk, struct tcp_info *info)
{
	info->tcpi_ca_state = ccid3_hc_rx_sk(sk)->rx_state;
	info->tcpi_options  |= TCPI_OPT_TIMESTAMPS;
	info->tcpi_rcv_rtt  = ccid3_hc_rx_sk(sk)->rx_rtt;
}