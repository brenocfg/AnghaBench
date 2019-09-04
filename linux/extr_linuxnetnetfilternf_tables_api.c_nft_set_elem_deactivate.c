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
struct nft_set_ext {int dummy; } ;
struct nft_set_elem {int /*<<< orphan*/  priv; } ;
struct nft_set {int /*<<< orphan*/  dtype; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  use; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFT_SET_EXT_DATA ; 
 int /*<<< orphan*/  NFT_SET_EXT_OBJREF ; 
 int /*<<< orphan*/  nft_data_release (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nft_set_ext* nft_set_elem_ext (struct nft_set const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nft_set_ext_data (struct nft_set_ext const*) ; 
 scalar_t__ nft_set_ext_exists (struct nft_set_ext const*,int /*<<< orphan*/ ) ; 
 TYPE_1__** nft_set_ext_obj (struct nft_set_ext const*) ; 

__attribute__((used)) static void nft_set_elem_deactivate(const struct net *net,
				    const struct nft_set *set,
				    struct nft_set_elem *elem)
{
	const struct nft_set_ext *ext = nft_set_elem_ext(set, elem->priv);

	if (nft_set_ext_exists(ext, NFT_SET_EXT_DATA))
		nft_data_release(nft_set_ext_data(ext), set->dtype);
	if (nft_set_ext_exists(ext, NFT_SET_EXT_OBJREF))
		(*nft_set_ext_obj(ext))->use--;
}