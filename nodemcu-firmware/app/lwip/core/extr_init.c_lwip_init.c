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

/* Variables and functions */
 int MEMP_NUM_TCP_PCB ; 
 int TCP_MAXRTX ; 
 int TCP_MSS ; 
 int TCP_SYNMAXRTX ; 
 int TCP_WND ; 
 int /*<<< orphan*/  _bss_end ; 
 int /*<<< orphan*/  autoip_init () ; 
 int /*<<< orphan*/  dns_init () ; 
 int /*<<< orphan*/  etharp_init () ; 
 int /*<<< orphan*/  igmp_init () ; 
 int /*<<< orphan*/  ip_init () ; 
 int /*<<< orphan*/  lwip_sanity_check () ; 
 int /*<<< orphan*/  lwip_socket_init () ; 
 int /*<<< orphan*/  mem_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memp_init () ; 
 int /*<<< orphan*/  netif_init () ; 
 int /*<<< orphan*/  pbuf_init () ; 
 int /*<<< orphan*/  raw_init () ; 
 int /*<<< orphan*/  snmp_init () ; 
 int /*<<< orphan*/  stats_init () ; 
 int /*<<< orphan*/  sys_init () ; 
 int /*<<< orphan*/  sys_timeouts_init () ; 
 int /*<<< orphan*/  tcp_init () ; 
 int /*<<< orphan*/  udp_init () ; 

void
lwip_init(void)
{
  MEMP_NUM_TCP_PCB = 5;
  TCP_WND = (4 * TCP_MSS);
  TCP_MAXRTX = 12;
  TCP_SYNMAXRTX = 6;

  /* Sanity check user-configurable values */
  lwip_sanity_check();

  /* Modules initialization */
  stats_init();
#if !NO_SYS
  sys_init();
#endif /* !NO_SYS */
#if 0
  mem_init(&_bss_end);
#endif
  memp_init();

  pbuf_init();

  netif_init();

#if LWIP_SOCKET
  lwip_socket_init();
#endif /* LWIP_SOCKET */
  ip_init();

#if LWIP_ARP
  etharp_init();

#endif /* LWIP_ARP */
#if LWIP_RAW
  raw_init();

#endif /* LWIP_RAW */
#if LWIP_UDP
  udp_init();

#endif /* LWIP_UDP */
#if LWIP_TCP
  tcp_init();

#endif /* LWIP_TCP */
#if LWIP_SNMP
  snmp_init();

#endif /* LWIP_SNMP */
#if LWIP_AUTOIP
  autoip_init();

#endif /* LWIP_AUTOIP */
#if LWIP_IGMP
  igmp_init();

#endif /* LWIP_IGMP */
#if LWIP_DNS
  dns_init();

#endif /* LWIP_DNS */

#if LWIP_TIMERS
  sys_timeouts_init();
#endif /* LWIP_TIMERS */
}