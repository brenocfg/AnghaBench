#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct xfrm_type {scalar_t__ proto; } ;
struct TYPE_4__ {int header_len; int mode; int /*<<< orphan*/  family; } ;
struct TYPE_3__ {scalar_t__ state; } ;
struct xfrm_state {TYPE_2__ props; struct crypto_aead* data; TYPE_1__ km; int /*<<< orphan*/  type; } ;
struct ipv6hdr {int dummy; } ;
struct iphdr {int dummy; } ;
struct crypto_aead {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int ALIGN (int /*<<< orphan*/ ,int) ; 
 scalar_t__ IPPROTO_ESP ; 
 struct xfrm_type* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
#define  XFRM_MODE_BEET 130 
#define  XFRM_MODE_TRANSPORT 129 
#define  XFRM_MODE_TUNNEL 128 
 scalar_t__ XFRM_STATE_VALID ; 
 int crypto_aead_authsize (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_blocksize (struct crypto_aead*) ; 

u32 xfrm_state_mtu(struct xfrm_state *x, int mtu)
{
	const struct xfrm_type *type = READ_ONCE(x->type);
	struct crypto_aead *aead;
	u32 blksize, net_adj = 0;

	if (x->km.state != XFRM_STATE_VALID ||
	    !type || type->proto != IPPROTO_ESP)
		return mtu - x->props.header_len;

	aead = x->data;
	blksize = ALIGN(crypto_aead_blocksize(aead), 4);

	switch (x->props.mode) {
	case XFRM_MODE_TRANSPORT:
	case XFRM_MODE_BEET:
		if (x->props.family == AF_INET)
			net_adj = sizeof(struct iphdr);
		else if (x->props.family == AF_INET6)
			net_adj = sizeof(struct ipv6hdr);
		break;
	case XFRM_MODE_TUNNEL:
		break;
	default:
		WARN_ON_ONCE(1);
		break;
	}

	return ((mtu - x->props.header_len - crypto_aead_authsize(aead) -
		 net_adj) & ~(blksize - 1)) + net_adj - 2;
}