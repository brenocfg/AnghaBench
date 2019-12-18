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
struct nft_flowtable {int /*<<< orphan*/  use; } ;
struct nft_ctx {int dummy; } ;
typedef  enum nft_trans_phase { ____Placeholder_nft_trans_phase } nft_trans_phase ;

/* Variables and functions */
#define  NFT_TRANS_ABORT 130 
#define  NFT_TRANS_PREPARE 129 
#define  NFT_TRANS_RELEASE 128 

void nf_tables_deactivate_flowtable(const struct nft_ctx *ctx,
				    struct nft_flowtable *flowtable,
				    enum nft_trans_phase phase)
{
	switch (phase) {
	case NFT_TRANS_PREPARE:
	case NFT_TRANS_ABORT:
	case NFT_TRANS_RELEASE:
		flowtable->use--;
		/* fall through */
	default:
		return;
	}
}