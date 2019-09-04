#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct sock {int dummy; } ;
struct list_head {int dummy; } ;
struct TYPE_6__ {scalar_t__ nn; } ;
struct dccp_feat_entry {scalar_t__ state; TYPE_1__ val; } ;
struct TYPE_7__ {scalar_t__ nn; } ;
typedef  TYPE_2__ dccp_feat_val ;
struct TYPE_8__ {struct list_head dccps_featneg; } ;

/* Variables and functions */
 scalar_t__ DCCPO_CHANGE_L ; 
 scalar_t__ DCCPO_CONFIRM_R ; 
 scalar_t__ DCCP_RESET_CODE_MANDATORY_ERROR ; 
 scalar_t__ DCCP_RESET_CODE_OPTION_ERROR ; 
 scalar_t__ DCCP_RESET_CODE_TOO_BUSY ; 
 int /*<<< orphan*/  DCCP_WARN (char*,scalar_t__) ; 
 scalar_t__ FEAT_CHANGING ; 
 scalar_t__ FEAT_NN ; 
 scalar_t__ FEAT_UNKNOWN ; 
 void* dccp_decode_value_var (scalar_t__*,scalar_t__) ; 
 scalar_t__ dccp_feat_activate (struct sock*,scalar_t__,int const,TYPE_2__*) ; 
 int /*<<< orphan*/  dccp_feat_is_valid_nn_val (scalar_t__,scalar_t__) ; 
 struct dccp_feat_entry* dccp_feat_list_lookup (struct list_head*,scalar_t__,int const) ; 
 int /*<<< orphan*/  dccp_feat_list_pop (struct dccp_feat_entry*) ; 
 int /*<<< orphan*/  dccp_feat_print_opt (scalar_t__,scalar_t__,scalar_t__*,scalar_t__,scalar_t__) ; 
 scalar_t__ dccp_feat_push_confirm (struct list_head*,scalar_t__,int const,TYPE_2__*) ; 
 scalar_t__ dccp_feat_type (scalar_t__) ; 
 scalar_t__ dccp_push_empty_confirm (struct list_head*,scalar_t__,int const) ; 
 TYPE_3__* dccp_sk (struct sock*) ; 
 int /*<<< orphan*/  inet_csk_schedule_ack (struct sock*) ; 

__attribute__((used)) static u8 dccp_feat_handle_nn_established(struct sock *sk, u8 mandatory, u8 opt,
					  u8 feat, u8 *val, u8 len)
{
	struct list_head *fn = &dccp_sk(sk)->dccps_featneg;
	const bool local = (opt == DCCPO_CONFIRM_R);
	struct dccp_feat_entry *entry;
	u8 type = dccp_feat_type(feat);
	dccp_feat_val fval;

	dccp_feat_print_opt(opt, feat, val, len, mandatory);

	/* Ignore non-mandatory unknown and non-NN features */
	if (type == FEAT_UNKNOWN) {
		if (local && !mandatory)
			return 0;
		goto fast_path_unknown;
	} else if (type != FEAT_NN) {
		return 0;
	}

	/*
	 * We don't accept empty Confirms, since in fast-path feature
	 * negotiation the values are enabled immediately after sending
	 * the Change option.
	 * Empty Changes on the other hand are invalid (RFC 4340, 6.1).
	 */
	if (len == 0 || len > sizeof(fval.nn))
		goto fast_path_unknown;

	if (opt == DCCPO_CHANGE_L) {
		fval.nn = dccp_decode_value_var(val, len);
		if (!dccp_feat_is_valid_nn_val(feat, fval.nn))
			goto fast_path_unknown;

		if (dccp_feat_push_confirm(fn, feat, local, &fval) ||
		    dccp_feat_activate(sk, feat, local, &fval))
			return DCCP_RESET_CODE_TOO_BUSY;

		/* set the `Ack Pending' flag to piggyback a Confirm */
		inet_csk_schedule_ack(sk);

	} else if (opt == DCCPO_CONFIRM_R) {
		entry = dccp_feat_list_lookup(fn, feat, local);
		if (entry == NULL || entry->state != FEAT_CHANGING)
			return 0;

		fval.nn = dccp_decode_value_var(val, len);
		/*
		 * Just ignore a value that doesn't match our current value.
		 * If the option changes twice within two RTTs, then at least
		 * one CONFIRM will be received for the old value after a
		 * new CHANGE was sent.
		 */
		if (fval.nn != entry->val.nn)
			return 0;

		/* Only activate after receiving the Confirm option (6.6.1). */
		dccp_feat_activate(sk, feat, local, &fval);

		/* It has been confirmed - so remove the entry */
		dccp_feat_list_pop(entry);

	} else {
		DCCP_WARN("Received illegal option %u\n", opt);
		goto fast_path_failed;
	}
	return 0;

fast_path_unknown:
	if (!mandatory)
		return dccp_push_empty_confirm(fn, feat, local);

fast_path_failed:
	return mandatory ? DCCP_RESET_CODE_MANDATORY_ERROR
			 : DCCP_RESET_CODE_OPTION_ERROR;
}