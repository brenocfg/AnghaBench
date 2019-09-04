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
struct nlattr {int dummy; } ;
struct nft_set_desc {int dummy; } ;
struct nft_set {int /*<<< orphan*/  klen; } ;
struct nft_bitmap {int /*<<< orphan*/  bitmap_size; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nft_bitmap_size (int /*<<< orphan*/ ) ; 
 struct nft_bitmap* nft_set_priv (struct nft_set const*) ; 

__attribute__((used)) static int nft_bitmap_init(const struct nft_set *set,
			 const struct nft_set_desc *desc,
			 const struct nlattr * const nla[])
{
	struct nft_bitmap *priv = nft_set_priv(set);

	INIT_LIST_HEAD(&priv->list);
	priv->bitmap_size = nft_bitmap_size(set->klen);

	return 0;
}