#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct sock {int dummy; } ;
struct TYPE_5__ {scalar_t__* vec; } ;
struct TYPE_6__ {scalar_t__ nn; TYPE_1__ sp; } ;
typedef  TYPE_2__ dccp_feat_val ;
struct TYPE_7__ {int (* activation_hdlr ) (struct sock*,scalar_t__,int) ;scalar_t__ reconciliation; scalar_t__ rxtx; int /*<<< orphan*/  feat_num; scalar_t__ default_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCCP_CRIT (char*,int const) ; 
 int const DCCP_FEAT_SUPPORTED_MAX ; 
 scalar_t__ FEAT_AT_RX ; 
 scalar_t__ FEAT_SP ; 
 int /*<<< orphan*/  dccp_debug (char*,char*,int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int /*<<< orphan*/  dccp_feat_fname (int /*<<< orphan*/ ) ; 
 TYPE_3__* dccp_feat_table ; 
 int stub1 (struct sock*,scalar_t__,int) ; 

__attribute__((used)) static int __dccp_feat_activate(struct sock *sk, const int idx,
				const bool is_local, dccp_feat_val const *fval)
{
	bool rx;
	u64 val;

	if (idx < 0 || idx >= DCCP_FEAT_SUPPORTED_MAX)
		return -1;
	if (dccp_feat_table[idx].activation_hdlr == NULL)
		return 0;

	if (fval == NULL) {
		val = dccp_feat_table[idx].default_value;
	} else if (dccp_feat_table[idx].reconciliation == FEAT_SP) {
		if (fval->sp.vec == NULL) {
			/*
			 * This can happen when an empty Confirm is sent
			 * for an SP (i.e. known) feature. In this case
			 * we would be using the default anyway.
			 */
			DCCP_CRIT("Feature #%d undefined: using default", idx);
			val = dccp_feat_table[idx].default_value;
		} else {
			val = fval->sp.vec[0];
		}
	} else {
		val = fval->nn;
	}

	/* Location is RX if this is a local-RX or remote-TX feature */
	rx = (is_local == (dccp_feat_table[idx].rxtx == FEAT_AT_RX));

	dccp_debug("   -> activating %s %s, %sval=%llu\n", rx ? "RX" : "TX",
		   dccp_feat_fname(dccp_feat_table[idx].feat_num),
		   fval ? "" : "default ",  (unsigned long long)val);

	return dccp_feat_table[idx].activation_hdlr(sk, val, rx);
}