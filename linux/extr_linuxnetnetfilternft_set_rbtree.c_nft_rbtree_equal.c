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
struct nft_set {int /*<<< orphan*/  klen; } ;
struct nft_rbtree_elem {int /*<<< orphan*/  ext; } ;

/* Variables and functions */
 scalar_t__ memcmp (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nft_set_ext_key (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool nft_rbtree_equal(const struct nft_set *set, const void *this,
			     const struct nft_rbtree_elem *interval)
{
	return memcmp(this, nft_set_ext_key(&interval->ext), set->klen) == 0;
}