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
struct TYPE_4__ {scalar_t__ mode; scalar_t__ trailer_len; scalar_t__ header_len; } ;
struct TYPE_3__ {scalar_t__ family; } ;
struct xfrm_state {TYPE_2__ props; struct xfrm_encap_tmpl* encap; TYPE_1__ sel; struct crypto_aead* data; scalar_t__ aead; } ;
struct xfrm_encap_tmpl {int encap_type; } ;
struct udphdr {int dummy; } ;
struct iphdr {int dummy; } ;
struct ip_esp_hdr {int dummy; } ;
struct crypto_aead {int dummy; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 scalar_t__ ALIGN (int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
 scalar_t__ IPV4_BEET_PHMAXLEN ; 
#define  UDP_ENCAP_ESPINUDP 129 
#define  UDP_ENCAP_ESPINUDP_NON_IKE 128 
 scalar_t__ XFRM_MODE_BEET ; 
 scalar_t__ XFRM_MODE_TUNNEL ; 
 scalar_t__ crypto_aead_authsize (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_blocksize (struct crypto_aead*) ; 
 scalar_t__ crypto_aead_ivsize (struct crypto_aead*) ; 
 int esp_init_aead (struct xfrm_state*) ; 
 int esp_init_authenc (struct xfrm_state*) ; 

__attribute__((used)) static int esp_init_state(struct xfrm_state *x)
{
	struct crypto_aead *aead;
	u32 align;
	int err;

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
	if (x->props.mode == XFRM_MODE_TUNNEL)
		x->props.header_len += sizeof(struct iphdr);
	else if (x->props.mode == XFRM_MODE_BEET && x->sel.family != AF_INET6)
		x->props.header_len += IPV4_BEET_PHMAXLEN;
	if (x->encap) {
		struct xfrm_encap_tmpl *encap = x->encap;

		switch (encap->encap_type) {
		default:
			err = -EINVAL;
			goto error;
		case UDP_ENCAP_ESPINUDP:
			x->props.header_len += sizeof(struct udphdr);
			break;
		case UDP_ENCAP_ESPINUDP_NON_IKE:
			x->props.header_len += sizeof(struct udphdr) + 2 * sizeof(u32);
			break;
		}
	}

	align = ALIGN(crypto_aead_blocksize(aead), 4);
	x->props.trailer_len = align + 1 + crypto_aead_authsize(aead);

error:
	return err;
}