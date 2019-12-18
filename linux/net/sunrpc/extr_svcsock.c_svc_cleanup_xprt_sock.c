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
 int /*<<< orphan*/  svc_tcp_class ; 
 int /*<<< orphan*/  svc_udp_class ; 
 int /*<<< orphan*/  svc_unreg_xprt_class (int /*<<< orphan*/ *) ; 

void svc_cleanup_xprt_sock(void)
{
	svc_unreg_xprt_class(&svc_tcp_class);
	svc_unreg_xprt_class(&svc_udp_class);
}