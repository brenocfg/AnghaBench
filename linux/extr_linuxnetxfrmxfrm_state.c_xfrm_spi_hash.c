#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfrm_address_t ;
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  state_hmask; } ;
struct net {TYPE_1__ xfrm; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 unsigned int __xfrm_spi_hash (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int
xfrm_spi_hash(struct net *net, const xfrm_address_t *daddr,
	      __be32 spi, u8 proto, unsigned short family)
{
	return __xfrm_spi_hash(daddr, spi, proto, family, net->xfrm.state_hmask);
}