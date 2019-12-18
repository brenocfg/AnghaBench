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
struct nft_set_dump_ctx {int dummy; } ;
struct netlink_callback {struct nft_set_dump_ctx* data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct nft_set_dump_ctx* kmemdup (struct nft_set_dump_ctx*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nf_tables_dump_set_start(struct netlink_callback *cb)
{
	struct nft_set_dump_ctx *dump_ctx = cb->data;

	cb->data = kmemdup(dump_ctx, sizeof(*dump_ctx), GFP_ATOMIC);

	return cb->data ? 0 : -ENOMEM;
}