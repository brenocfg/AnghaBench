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
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int inet_cidr_pton_ipv6 (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
inet_net_pton_ipv6(const char *src, u_char *dst)
{
	return inet_cidr_pton_ipv6(src, dst, 16);
}