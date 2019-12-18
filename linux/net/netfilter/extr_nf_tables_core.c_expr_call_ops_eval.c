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
struct nft_expr {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* eval ) (struct nft_expr const*,struct nft_regs*,struct nft_pktinfo*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  X (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nft_bitwise_eval ; 
 int /*<<< orphan*/  nft_byteorder_eval ; 
 int /*<<< orphan*/  nft_cmp_eval ; 
 int /*<<< orphan*/  nft_dynset_eval ; 
 int /*<<< orphan*/  nft_immediate_eval ; 
 int /*<<< orphan*/  nft_lookup_eval ; 
 int /*<<< orphan*/  nft_meta_get_eval ; 
 int /*<<< orphan*/  nft_payload_eval ; 
 int /*<<< orphan*/  nft_range_eval ; 
 int /*<<< orphan*/  nft_rt_get_eval ; 
 int /*<<< orphan*/  stub1 (struct nft_expr const*,struct nft_regs*,struct nft_pktinfo*) ; 

__attribute__((used)) static void expr_call_ops_eval(const struct nft_expr *expr,
			       struct nft_regs *regs,
			       struct nft_pktinfo *pkt)
{
#ifdef CONFIG_RETPOLINE
	unsigned long e = (unsigned long)expr->ops->eval;
#define X(e, fun) \
	do { if ((e) == (unsigned long)(fun)) \
		return fun(expr, regs, pkt); } while (0)

	X(e, nft_payload_eval);
	X(e, nft_cmp_eval);
	X(e, nft_meta_get_eval);
	X(e, nft_lookup_eval);
	X(e, nft_range_eval);
	X(e, nft_immediate_eval);
	X(e, nft_byteorder_eval);
	X(e, nft_dynset_eval);
	X(e, nft_rt_get_eval);
	X(e, nft_bitwise_eval);
#undef  X
#endif /* CONFIG_RETPOLINE */
	expr->ops->eval(expr, regs, pkt);
}