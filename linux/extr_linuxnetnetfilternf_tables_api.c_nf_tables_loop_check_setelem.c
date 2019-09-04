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
struct nft_set_iter {int dummy; } ;
struct nft_set_ext {int dummy; } ;
struct nft_set_elem {int /*<<< orphan*/  priv; } ;
struct nft_set {int dummy; } ;
struct TYPE_2__ {int code; int /*<<< orphan*/  chain; } ;
struct nft_data {TYPE_1__ verdict; } ;
struct nft_ctx {int dummy; } ;

/* Variables and functions */
#define  NFT_GOTO 129 
#define  NFT_JUMP 128 
 int NFT_SET_ELEM_INTERVAL_END ; 
 int /*<<< orphan*/  NFT_SET_EXT_FLAGS ; 
 int nf_tables_check_loops (struct nft_ctx const*,int /*<<< orphan*/ ) ; 
 struct nft_set_ext* nft_set_elem_ext (struct nft_set*,int /*<<< orphan*/ ) ; 
 struct nft_data* nft_set_ext_data (struct nft_set_ext const*) ; 
 scalar_t__ nft_set_ext_exists (struct nft_set_ext const*,int /*<<< orphan*/ ) ; 
 int* nft_set_ext_flags (struct nft_set_ext const*) ; 

__attribute__((used)) static int nf_tables_loop_check_setelem(const struct nft_ctx *ctx,
					struct nft_set *set,
					const struct nft_set_iter *iter,
					struct nft_set_elem *elem)
{
	const struct nft_set_ext *ext = nft_set_elem_ext(set, elem->priv);
	const struct nft_data *data;

	if (nft_set_ext_exists(ext, NFT_SET_EXT_FLAGS) &&
	    *nft_set_ext_flags(ext) & NFT_SET_ELEM_INTERVAL_END)
		return 0;

	data = nft_set_ext_data(ext);
	switch (data->verdict.code) {
	case NFT_JUMP:
	case NFT_GOTO:
		return nf_tables_check_loops(ctx, data->verdict.chain);
	default:
		return 0;
	}
}