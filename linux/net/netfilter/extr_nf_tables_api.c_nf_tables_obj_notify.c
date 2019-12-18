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
struct nft_object {int dummy; } ;
struct nft_ctx {int /*<<< orphan*/  report; int /*<<< orphan*/  family; int /*<<< orphan*/  seq; int /*<<< orphan*/  portid; int /*<<< orphan*/  table; int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  nft_obj_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nft_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nf_tables_obj_notify(const struct nft_ctx *ctx,
				 struct nft_object *obj, int event)
{
	nft_obj_notify(ctx->net, ctx->table, obj, ctx->portid, ctx->seq, event,
		       ctx->family, ctx->report, GFP_KERNEL);
}