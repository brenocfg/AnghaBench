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
struct nft_synproxy {int dummy; } ;
struct nft_object {int dummy; } ;
struct nft_ctx {int dummy; } ;

/* Variables and functions */
 struct nft_synproxy* nft_obj_data (struct nft_object*) ; 
 int nft_synproxy_do_init (struct nft_ctx const*,struct nlattr const* const*,struct nft_synproxy*) ; 

__attribute__((used)) static int nft_synproxy_obj_init(const struct nft_ctx *ctx,
				 const struct nlattr * const tb[],
				 struct nft_object *obj)
{
	struct nft_synproxy *priv = nft_obj_data(obj);

	return nft_synproxy_do_init(ctx, tb, priv);
}