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
struct rhashtable_compare_arg {struct nft_object_hash_key* key; } ;
struct nft_object_hash_key {scalar_t__ table; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {scalar_t__ table; int /*<<< orphan*/  name; } ;
struct nft_object {TYPE_1__ key; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_objname_hash_cmp(struct rhashtable_compare_arg *arg,
				const void *ptr)
{
	const struct nft_object_hash_key *k = arg->key;
	const struct nft_object *obj = ptr;

	if (obj->key.table != k->table)
		return -1;

	return strcmp(obj->key.name, k->name);
}