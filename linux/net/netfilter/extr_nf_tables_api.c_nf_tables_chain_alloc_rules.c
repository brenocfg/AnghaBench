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
struct nft_rules_old {int dummy; } ;
struct nft_rule {int dummy; } ;
struct nft_chain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int INT_MAX ; 
 struct nft_rule** kvmalloc (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nft_rule **nf_tables_chain_alloc_rules(const struct nft_chain *chain,
						     unsigned int alloc)
{
	if (alloc > INT_MAX)
		return NULL;

	alloc += 1;	/* NULL, ends rules */
	if (sizeof(struct nft_rule *) > INT_MAX / alloc)
		return NULL;

	alloc *= sizeof(struct nft_rule *);
	alloc += sizeof(struct nft_rules_old);

	return kvmalloc(alloc, GFP_KERNEL);
}