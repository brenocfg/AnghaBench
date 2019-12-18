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
 int net_addr_v4_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*,int,char*) ; 

__attribute__((used)) static int
net__addr_v4_add(const char *addr_str, int prefixlen)
{
    in_addr_t addr;
    int ret;

    ret = inet_pton(AF_INET, addr_str, &addr);
    if (ret != 1)
        return -1;

    addr = ntohl(addr);

    printf("CMD: ip addr add %s/%d dev %s\n", addr_str, prefixlen, iface);

    return net_addr_v4_add(NULL, iface, &addr, prefixlen);
}