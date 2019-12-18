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
struct nft_object {int /*<<< orphan*/  list; int /*<<< orphan*/  rhlhead; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nft_objname_ht ; 
 int /*<<< orphan*/  nft_objname_ht_params ; 
 int /*<<< orphan*/  rhltable_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nft_obj_del(struct nft_object *obj)
{
	rhltable_remove(&nft_objname_ht, &obj->rhlhead, nft_objname_ht_params);
	list_del_rcu(&obj->list);
}