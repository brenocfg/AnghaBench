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
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 char* iface ; 
 int inet_pton (int /*<<< orphan*/ ,char const*,struct in6_addr*) ; 
 int net_route_v6_add (int /*<<< orphan*/ *,struct in6_addr*,int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
net__route_v6_add(const char *dst_str, int prefixlen, int metric)
{
    struct in6_addr dst;
    int ret;

    if (!dst_str)
        return -1;

    ret = inet_pton(AF_INET6, dst_str, &dst);
    if (ret != 1)
        return -1;

    printf("CMD: ip -6 route add %s/%d dev %s", dst_str, prefixlen, iface);
    if (metric > 0)
        printf(" metric %d", metric);
    printf("\n");

    return net_route_v6_add(NULL, &dst, prefixlen, NULL, iface, 0, metric);

}