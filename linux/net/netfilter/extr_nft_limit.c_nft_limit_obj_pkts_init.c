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
struct nlattr {int dummy; } ;
struct nft_object {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rate; int /*<<< orphan*/  nsecs; } ;
struct nft_limit_pkts {TYPE_1__ limit; int /*<<< orphan*/  cost; } ;
struct nft_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  div64_u64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nft_limit_init (TYPE_1__*,struct nlattr const* const*,int) ; 
 struct nft_limit_pkts* nft_obj_data (struct nft_object*) ; 

__attribute__((used)) static int nft_limit_obj_pkts_init(const struct nft_ctx *ctx,
				   const struct nlattr * const tb[],
				   struct nft_object *obj)
{
	struct nft_limit_pkts *priv = nft_obj_data(obj);
	int err;

	err = nft_limit_init(&priv->limit, tb, true);
	if (err < 0)
		return err;

	priv->cost = div64_u64(priv->limit.nsecs, priv->limit.rate);
	return 0;
}