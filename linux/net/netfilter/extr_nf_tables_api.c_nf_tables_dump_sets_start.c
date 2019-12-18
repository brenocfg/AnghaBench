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
struct nft_ctx {int dummy; } ;
struct netlink_callback {struct nft_ctx* data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct nft_ctx* kmemdup (struct nft_ctx*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nf_tables_dump_sets_start(struct netlink_callback *cb)
{
	struct nft_ctx *ctx_dump = NULL;

	ctx_dump = kmemdup(cb->data, sizeof(*ctx_dump), GFP_ATOMIC);
	if (ctx_dump == NULL)
		return -ENOMEM;

	cb->data = ctx_dump;
	return 0;
}