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
struct rhashtable_compare_arg {char* key; } ;
struct nft_chain {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int nft_chain_hash_cmp(struct rhashtable_compare_arg *arg,
			      const void *ptr)
{
	const struct nft_chain *chain = ptr;
	const char *name = arg->key;

	return strcmp(chain->name, name);
}