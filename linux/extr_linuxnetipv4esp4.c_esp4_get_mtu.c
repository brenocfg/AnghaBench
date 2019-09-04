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
struct TYPE_2__ {int mode; int header_len; } ;
struct xfrm_state {TYPE_1__ props; struct crypto_aead* data; } ;
struct iphdr {int dummy; } ;
struct crypto_aead {int dummy; } ;

/* Variables and functions */
 int ALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BUG () ; 
#define  XFRM_MODE_BEET 130 
#define  XFRM_MODE_TRANSPORT 129 
#define  XFRM_MODE_TUNNEL 128 
 int crypto_aead_authsize (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_blocksize (struct crypto_aead*) ; 

__attribute__((used)) static u32 esp4_get_mtu(struct xfrm_state *x, int mtu)
{
	struct crypto_aead *aead = x->data;
	u32 blksize = ALIGN(crypto_aead_blocksize(aead), 4);
	unsigned int net_adj;

	switch (x->props.mode) {
	case XFRM_MODE_TRANSPORT:
	case XFRM_MODE_BEET:
		net_adj = sizeof(struct iphdr);
		break;
	case XFRM_MODE_TUNNEL:
		net_adj = 0;
		break;
	default:
		BUG();
	}

	return ((mtu - x->props.header_len - crypto_aead_authsize(aead) -
		 net_adj) & ~(blksize - 1)) + net_adj - 2;
}