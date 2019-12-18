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
typedef  int u8 ;
struct TYPE_2__ {int validate_state; } ;
struct net {TYPE_1__ nft; } ;

/* Variables and functions */
#define  NFT_VALIDATE_DO 130 
#define  NFT_VALIDATE_NEED 129 
#define  NFT_VALIDATE_SKIP 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

__attribute__((used)) static void nft_validate_state_update(struct net *net, u8 new_validate_state)
{
	switch (net->nft.validate_state) {
	case NFT_VALIDATE_SKIP:
		WARN_ON_ONCE(new_validate_state == NFT_VALIDATE_DO);
		break;
	case NFT_VALIDATE_NEED:
		break;
	case NFT_VALIDATE_DO:
		if (new_validate_state == NFT_VALIDATE_NEED)
			return;
	}

	net->nft.validate_state = new_validate_state;
}