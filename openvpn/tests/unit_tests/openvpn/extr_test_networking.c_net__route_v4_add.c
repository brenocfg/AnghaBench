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
typedef  int /*<<< orphan*/  in_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 char* iface ; 
 int inet_pton (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int net_route_v4_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
net__route_v4_add(const char *dst_str, int prefixlen, int metric)
{
    in_addr_t dst;
    int ret;

    if (!dst_str)
        return -1;

    ret = inet_pton(AF_INET, dst_str, &dst);
    if (ret != 1)
        return -1;

    dst = ntohl(dst);

    printf("CMD: ip route add %s/%d dev %s", dst_str, prefixlen, iface);
    if (metric > 0)
        printf(" metric %d", metric);
    printf("\n");

    return net_route_v4_add(NULL, &dst, prefixlen, NULL, iface, 0, metric);

}