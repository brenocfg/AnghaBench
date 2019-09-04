#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct common_audit_data {int dummy; } ;
struct audit_buffer {int dummy; } ;
typedef  int /*<<< orphan*/  kuid_t ;
struct TYPE_3__ {scalar_t__ target; int /*<<< orphan*/  ouid; } ;
struct TYPE_4__ {int request; int denied; TYPE_1__ fs; scalar_t__ peer; int /*<<< orphan*/  label; } ;

/* Variables and functions */
 int AA_AUDIT_FILE_MASK ; 
 int /*<<< orphan*/  FLAG_VIEW_SUBNS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  aa_label_xaudit (struct audit_buffer*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* aad (struct common_audit_data*) ; 
 int /*<<< orphan*/  audit_file_mask (struct audit_buffer*,int) ; 
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*,...) ; 
 int /*<<< orphan*/  audit_log_untrustedstring (struct audit_buffer*,scalar_t__) ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int /*<<< orphan*/  from_kuid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  labels_ns (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void file_audit_cb(struct audit_buffer *ab, void *va)
{
	struct common_audit_data *sa = va;
	kuid_t fsuid = current_fsuid();

	if (aad(sa)->request & AA_AUDIT_FILE_MASK) {
		audit_log_format(ab, " requested_mask=");
		audit_file_mask(ab, aad(sa)->request);
	}
	if (aad(sa)->denied & AA_AUDIT_FILE_MASK) {
		audit_log_format(ab, " denied_mask=");
		audit_file_mask(ab, aad(sa)->denied);
	}
	if (aad(sa)->request & AA_AUDIT_FILE_MASK) {
		audit_log_format(ab, " fsuid=%d",
				 from_kuid(&init_user_ns, fsuid));
		audit_log_format(ab, " ouid=%d",
				 from_kuid(&init_user_ns, aad(sa)->fs.ouid));
	}

	if (aad(sa)->peer) {
		audit_log_format(ab, " target=");
		aa_label_xaudit(ab, labels_ns(aad(sa)->label), aad(sa)->peer,
				FLAG_VIEW_SUBNS, GFP_ATOMIC);
	} else if (aad(sa)->fs.target) {
		audit_log_format(ab, " target=");
		audit_log_untrustedstring(ab, aad(sa)->fs.target);
	}
}