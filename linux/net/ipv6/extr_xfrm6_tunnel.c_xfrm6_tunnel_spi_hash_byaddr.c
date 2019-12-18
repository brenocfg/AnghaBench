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
typedef  int /*<<< orphan*/  xfrm_address_t ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int XFRM6_TUNNEL_SPI_BYADDR_HSIZE ; 
 unsigned int ipv6_addr_hash (struct in6_addr const*) ; 

__attribute__((used)) static inline unsigned int xfrm6_tunnel_spi_hash_byaddr(const xfrm_address_t *addr)
{
	unsigned int h;

	h = ipv6_addr_hash((const struct in6_addr *)addr);
	h ^= h >> 16;
	h ^= h >> 8;
	h &= XFRM6_TUNNEL_SPI_BYADDR_HSIZE - 1;

	return h;
}