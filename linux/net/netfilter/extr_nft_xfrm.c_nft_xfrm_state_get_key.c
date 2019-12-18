#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int /*<<< orphan*/  in6; int /*<<< orphan*/  a4; } ;
struct TYPE_9__ {int /*<<< orphan*/  spi; TYPE_1__ daddr; } ;
struct TYPE_7__ {int /*<<< orphan*/  in6; int /*<<< orphan*/  a4; } ;
struct TYPE_8__ {int /*<<< orphan*/  reqid; TYPE_2__ saddr; int /*<<< orphan*/  mode; int /*<<< orphan*/  family; } ;
struct xfrm_state {TYPE_4__ id; TYPE_3__ props; } ;
struct nft_xfrm {size_t dreg; int key; } ;
struct TYPE_10__ {void* code; } ;
struct nft_regs {TYPE_5__ verdict; int /*<<< orphan*/ * data; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 void* NFT_BREAK ; 
#define  NFT_XFRM_KEY_DADDR_IP4 135 
#define  NFT_XFRM_KEY_DADDR_IP6 134 
#define  NFT_XFRM_KEY_REQID 133 
#define  NFT_XFRM_KEY_SADDR_IP4 132 
#define  NFT_XFRM_KEY_SADDR_IP6 131 
#define  NFT_XFRM_KEY_SPI 130 
#define  NFT_XFRM_KEY_UNSPEC 129 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
#define  __NFT_XFRM_KEY_MAX 128 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xfrm_state_addr_ok (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nft_xfrm_state_get_key(const struct nft_xfrm *priv,
				   struct nft_regs *regs,
				   const struct xfrm_state *state)
{
	u32 *dest = &regs->data[priv->dreg];

	if (!xfrm_state_addr_ok(priv->key,
				state->props.family,
				state->props.mode)) {
		regs->verdict.code = NFT_BREAK;
		return;
	}

	switch (priv->key) {
	case NFT_XFRM_KEY_UNSPEC:
	case __NFT_XFRM_KEY_MAX:
		WARN_ON_ONCE(1);
		break;
	case NFT_XFRM_KEY_DADDR_IP4:
		*dest = state->id.daddr.a4;
		return;
	case NFT_XFRM_KEY_DADDR_IP6:
		memcpy(dest, &state->id.daddr.in6, sizeof(struct in6_addr));
		return;
	case NFT_XFRM_KEY_SADDR_IP4:
		*dest = state->props.saddr.a4;
		return;
	case NFT_XFRM_KEY_SADDR_IP6:
		memcpy(dest, &state->props.saddr.in6, sizeof(struct in6_addr));
		return;
	case NFT_XFRM_KEY_REQID:
		*dest = state->props.reqid;
		return;
	case NFT_XFRM_KEY_SPI:
		*dest = state->id.spi;
		return;
	}

	regs->verdict.code = NFT_BREAK;
}