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
typedef  int /*<<< orphan*/  ip_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  socket_dns_found (char const*,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static void socket_dns_foundcb(const char *name, ip_addr_t *ipaddr, void *arg)
{
  socket_dns_found(name, ipaddr, arg);
}