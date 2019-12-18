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
struct nft_synproxy {int /*<<< orphan*/  info; } ;
struct nft_object {int dummy; } ;

/* Variables and functions */
 struct nft_synproxy* nft_obj_data (struct nft_object*) ; 

__attribute__((used)) static void nft_synproxy_obj_update(struct nft_object *obj,
				    struct nft_object *newobj)
{
	struct nft_synproxy *newpriv = nft_obj_data(newobj);
	struct nft_synproxy *priv = nft_obj_data(obj);

	priv->info = newpriv->info;
}