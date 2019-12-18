#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nft_set {scalar_t__ use; int /*<<< orphan*/  name; TYPE_2__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* destroy ) (struct nft_set*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (struct nft_set*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct nft_set*) ; 
 TYPE_1__* to_set_type (TYPE_2__*) ; 

__attribute__((used)) static void nft_set_destroy(struct nft_set *set)
{
	if (WARN_ON(set->use > 0))
		return;

	set->ops->destroy(set);
	module_put(to_set_type(set->ops)->owner);
	kfree(set->name);
	kvfree(set);
}