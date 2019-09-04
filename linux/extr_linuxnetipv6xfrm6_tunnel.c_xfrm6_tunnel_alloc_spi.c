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
typedef  int /*<<< orphan*/  u32 ;
struct xfrm6_tunnel_spi {int /*<<< orphan*/  spi; int /*<<< orphan*/  refcnt; } ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  __xfrm6_tunnel_alloc_spi (struct net*,int /*<<< orphan*/ *) ; 
 struct xfrm6_tunnel_spi* __xfrm6_tunnel_spi_lookup (struct net*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfrm6_tunnel_spi_lock ; 

__be32 xfrm6_tunnel_alloc_spi(struct net *net, xfrm_address_t *saddr)
{
	struct xfrm6_tunnel_spi *x6spi;
	u32 spi;

	spin_lock_bh(&xfrm6_tunnel_spi_lock);
	x6spi = __xfrm6_tunnel_spi_lookup(net, saddr);
	if (x6spi) {
		refcount_inc(&x6spi->refcnt);
		spi = x6spi->spi;
	} else
		spi = __xfrm6_tunnel_alloc_spi(net, saddr);
	spin_unlock_bh(&xfrm6_tunnel_spi_lock);

	return htonl(spi);
}