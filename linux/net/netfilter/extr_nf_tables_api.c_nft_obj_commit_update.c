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
struct nft_trans {int dummy; } ;
struct nft_object {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* update ) (struct nft_object*,struct nft_object*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nft_object*) ; 
 struct nft_object* nft_trans_obj (struct nft_trans*) ; 
 struct nft_object* nft_trans_obj_newobj (struct nft_trans*) ; 
 int /*<<< orphan*/  stub1 (struct nft_object*,struct nft_object*) ; 

__attribute__((used)) static void nft_obj_commit_update(struct nft_trans *trans)
{
	struct nft_object *newobj;
	struct nft_object *obj;

	obj = nft_trans_obj(trans);
	newobj = nft_trans_obj_newobj(trans);

	if (obj->ops->update)
		obj->ops->update(obj, newobj);

	kfree(newobj);
}