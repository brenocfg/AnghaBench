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
struct common_audit_data {int dummy; } ;
struct audit_buffer {int dummy; } ;
struct TYPE_2__ {int request; int denied; size_t signal; int /*<<< orphan*/  peer; int /*<<< orphan*/  label; int /*<<< orphan*/  unmappedsig; } ;

/* Variables and functions */
 int AA_SIGNAL_PERM_MASK ; 
 int /*<<< orphan*/  FLAGS_NONE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 size_t MAXMAPPED_SIGNAME ; 
 scalar_t__ SIGRT_BASE ; 
 size_t SIGUNKNOWN ; 
 int /*<<< orphan*/  aa_label_xaudit (struct audit_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* aad (struct common_audit_data*) ; 
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*,...) ; 
 int /*<<< orphan*/  audit_signal_mask (struct audit_buffer*,int) ; 
 int /*<<< orphan*/  labels_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sig_names ; 

__attribute__((used)) static void audit_signal_cb(struct audit_buffer *ab, void *va)
{
	struct common_audit_data *sa = va;

	if (aad(sa)->request & AA_SIGNAL_PERM_MASK) {
		audit_log_format(ab, " requested_mask=");
		audit_signal_mask(ab, aad(sa)->request);
		if (aad(sa)->denied & AA_SIGNAL_PERM_MASK) {
			audit_log_format(ab, " denied_mask=");
			audit_signal_mask(ab, aad(sa)->denied);
		}
	}
	if (aad(sa)->signal == SIGUNKNOWN)
		audit_log_format(ab, "signal=unknown(%d)",
				 aad(sa)->unmappedsig);
	else if (aad(sa)->signal < MAXMAPPED_SIGNAME)
		audit_log_format(ab, " signal=%s", sig_names[aad(sa)->signal]);
	else
		audit_log_format(ab, " signal=rtmin+%d",
				 aad(sa)->signal - SIGRT_BASE);
	audit_log_format(ab, " peer=");
	aa_label_xaudit(ab, labels_ns(aad(sa)->label), aad(sa)->peer,
			FLAGS_NONE, GFP_ATOMIC);
}