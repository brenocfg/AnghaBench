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
typedef  scalar_t__ u32 ;
struct TYPE_4__ {int mode; scalar_t__ trailer_len; scalar_t__ header_len; } ;
struct TYPE_3__ {int /*<<< orphan*/  family; } ;
struct xfrm_state {TYPE_2__ props; TYPE_1__ sel; struct crypto_aead* data; scalar_t__ aead; scalar_t__ encap; } ;
struct ipv6hdr {int dummy; } ;
struct iphdr {int dummy; } ;
struct ip_esp_hdr {int dummy; } ;
struct crypto_aead {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 scalar_t__ ALIGN (int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  IPV4_BEET_PHMAXLEN ; 
#define  XFRM_MODE_BEET 130 
#define  XFRM_MODE_TRANSPORT 129 
#define  XFRM_MODE_TUNNEL 128 
 scalar_t__ crypto_aead_authsize (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_blocksize (struct crypto_aead*) ; 
 scalar_t__ crypto_aead_ivsize (struct crypto_aead*) ; 
 int esp_init_aead (struct xfrm_state*) ; 
 int esp_init_authenc (struct xfrm_state*) ; 

__attribute__((used)) static int esp6_init_state(struct xfrm_state *x)
{
	struct crypto_aead *aead;
	u32 align;
	int err;

	if (x->encap)
		return -EINVAL;

	x->data = NULL;

	if (x->aead)
		err = esp_init_aead(x);
	else
		err = esp_init_authenc(x);

	if (err)
		goto error;

	aead = x->data;

	x->props.header_len = sizeof(struct ip_esp_hdr) +
			      crypto_aead_ivsize(aead);
	switch (x->props.mode) {
	case XFRM_MODE_BEET:
		if (x->sel.family != AF_INET6)
			x->props.header_len += IPV4_BEET_PHMAXLEN +
					       (sizeof(struct ipv6hdr) - sizeof(struct iphdr));
		break;
	default:
	case XFRM_MODE_TRANSPORT:
		break;
	case XFRM_MODE_TUNNEL:
		x->props.header_len += sizeof(struct ipv6hdr);
		break;
	}

	align = ALIGN(crypto_aead_blocksize(aead), 4);
	x->props.trailer_len = align + 1 + crypto_aead_authsize(aead);

error:
	return err;
}