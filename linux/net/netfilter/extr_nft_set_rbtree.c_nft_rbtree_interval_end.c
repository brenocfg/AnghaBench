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
struct nft_rbtree_elem {int /*<<< orphan*/  ext; } ;

/* Variables and functions */
 int NFT_SET_ELEM_INTERVAL_END ; 
 int /*<<< orphan*/  NFT_SET_EXT_FLAGS ; 
 scalar_t__ nft_set_ext_exists (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int* nft_set_ext_flags (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool nft_rbtree_interval_end(const struct nft_rbtree_elem *rbe)
{
	return nft_set_ext_exists(&rbe->ext, NFT_SET_EXT_FLAGS) &&
	       (*nft_set_ext_flags(&rbe->ext) & NFT_SET_ELEM_INTERVAL_END);
}