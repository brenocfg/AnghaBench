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
 int /*<<< orphan*/  M_WARN ; 
 int get_ipv6_addr (char const*,struct in6_addr*,unsigned int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
ipv6_addr_safe_hexplusbits( const char *ipv6_prefix_spec )
{
    struct in6_addr t_addr;
    unsigned int t_bits;

    return get_ipv6_addr( ipv6_prefix_spec, &t_addr, &t_bits, M_WARN );
}