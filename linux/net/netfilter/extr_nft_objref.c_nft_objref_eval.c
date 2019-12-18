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
struct nft_regs {int dummy; } ;
struct nft_pktinfo {int dummy; } ;
struct nft_object {TYPE_1__* ops; } ;
struct nft_expr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* eval ) (struct nft_object*,struct nft_regs*,struct nft_pktinfo const*) ;} ;

/* Variables and functions */
 struct nft_object* nft_objref_priv (struct nft_expr const*) ; 
 int /*<<< orphan*/  stub1 (struct nft_object*,struct nft_regs*,struct nft_pktinfo const*) ; 

__attribute__((used)) static void nft_objref_eval(const struct nft_expr *expr,
			    struct nft_regs *regs,
			    const struct nft_pktinfo *pkt)
{
	struct nft_object *obj = nft_objref_priv(expr);

	obj->ops->eval(obj, regs, pkt);
}