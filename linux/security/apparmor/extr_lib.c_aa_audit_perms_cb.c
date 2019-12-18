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
struct TYPE_2__ {int /*<<< orphan*/  peer; int /*<<< orphan*/  label; scalar_t__ denied; scalar_t__ request; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAGS_NONE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PERMS_CHRS_MASK ; 
 int /*<<< orphan*/  PERMS_NAMES_MASK ; 
 int /*<<< orphan*/  aa_audit_perm_mask (struct audit_buffer*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aa_file_perm_chrs ; 
 int /*<<< orphan*/  aa_file_perm_names ; 
 int /*<<< orphan*/  aa_label_xaudit (struct audit_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* aad (struct common_audit_data*) ; 
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*) ; 
 int /*<<< orphan*/  labels_ns (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aa_audit_perms_cb(struct audit_buffer *ab, void *va)
{
	struct common_audit_data *sa = va;

	if (aad(sa)->request) {
		audit_log_format(ab, " requested_mask=");
		aa_audit_perm_mask(ab, aad(sa)->request, aa_file_perm_chrs,
				   PERMS_CHRS_MASK, aa_file_perm_names,
				   PERMS_NAMES_MASK);
	}
	if (aad(sa)->denied) {
		audit_log_format(ab, "denied_mask=");
		aa_audit_perm_mask(ab, aad(sa)->denied, aa_file_perm_chrs,
				   PERMS_CHRS_MASK, aa_file_perm_names,
				   PERMS_NAMES_MASK);
	}
	audit_log_format(ab, " peer=");
	aa_label_xaudit(ab, labels_ns(aad(sa)->label), aad(sa)->peer,
				      FLAGS_NONE, GFP_ATOMIC);
}