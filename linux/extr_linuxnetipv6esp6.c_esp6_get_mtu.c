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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ mode; int header_len; } ;
struct xfrm_state {TYPE_1__ props; struct crypto_aead* data; } ;
struct ipv6hdr {int dummy; } ;
struct crypto_aead {int dummy; } ;

/* Variables and functions */
 int ALIGN (int /*<<< orphan*/ ,int) ; 
 scalar_t__ XFRM_MODE_TUNNEL ; 
 int crypto_aead_authsize (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_blocksize (struct crypto_aead*) ; 

__attribute__((used)) static u32 esp6_get_mtu(struct xfrm_state *x, int mtu)
{
	struct crypto_aead *aead = x->data;
	u32 blksize = ALIGN(crypto_aead_blocksize(aead), 4);
	unsigned int net_adj;

	if (x->props.mode != XFRM_MODE_TUNNEL)
		net_adj = sizeof(struct ipv6hdr);
	else
		net_adj = 0;

	return ((mtu - x->props.header_len - crypto_aead_authsize(aead) -
		 net_adj) & ~(blksize - 1)) + net_adj - 2;
}