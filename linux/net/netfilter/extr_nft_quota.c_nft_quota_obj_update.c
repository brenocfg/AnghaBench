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
typedef  int /*<<< orphan*/  u64 ;
struct nft_quota {int /*<<< orphan*/  flags; int /*<<< orphan*/  quota; } ;
struct nft_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nft_quota* nft_obj_data (struct nft_object*) ; 

__attribute__((used)) static void nft_quota_obj_update(struct nft_object *obj,
				 struct nft_object *newobj)
{
	struct nft_quota *newpriv = nft_obj_data(newobj);
	struct nft_quota *priv = nft_obj_data(obj);
	u64 newquota;

	newquota = atomic64_read(&newpriv->quota);
	atomic64_set(&priv->quota, newquota);
	priv->flags = newpriv->flags;
}