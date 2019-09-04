#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct common_audit_data {int dummy; } ;
struct audit_buffer {int dummy; } ;
struct TYPE_7__ {scalar_t__ hname; } ;
struct aa_profile {TYPE_2__ base; TYPE_3__* ns; } ;
struct aa_label {int dummy; } ;
struct TYPE_9__ {size_t type; scalar_t__ name; struct aa_label* label; scalar_t__ error; scalar_t__ info; scalar_t__ op; } ;
struct TYPE_6__ {scalar_t__ hname; } ;
struct TYPE_8__ {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_VIEW_SUBNS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__* aa_audit_type ; 
 scalar_t__ aa_g_audit_header ; 
 int /*<<< orphan*/  aa_label_xaudit (struct audit_buffer*,TYPE_3__*,struct aa_label*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* aad (struct common_audit_data*) ; 
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*,...) ; 
 int /*<<< orphan*/  audit_log_string (struct audit_buffer*,scalar_t__) ; 
 int /*<<< orphan*/  audit_log_untrustedstring (struct audit_buffer*,scalar_t__) ; 
 scalar_t__ label_isprofile (struct aa_label*) ; 
 struct aa_profile* labels_profile (struct aa_label*) ; 
 TYPE_3__* root_ns ; 

__attribute__((used)) static void audit_pre(struct audit_buffer *ab, void *ca)
{
	struct common_audit_data *sa = ca;

	if (aa_g_audit_header) {
		audit_log_format(ab, "apparmor=");
		audit_log_string(ab, aa_audit_type[aad(sa)->type]);
	}

	if (aad(sa)->op) {
		audit_log_format(ab, " operation=");
		audit_log_string(ab, aad(sa)->op);
	}

	if (aad(sa)->info) {
		audit_log_format(ab, " info=");
		audit_log_string(ab, aad(sa)->info);
		if (aad(sa)->error)
			audit_log_format(ab, " error=%d", aad(sa)->error);
	}

	if (aad(sa)->label) {
		struct aa_label *label = aad(sa)->label;

		if (label_isprofile(label)) {
			struct aa_profile *profile = labels_profile(label);

			if (profile->ns != root_ns) {
				audit_log_format(ab, " namespace=");
				audit_log_untrustedstring(ab,
						       profile->ns->base.hname);
			}
			audit_log_format(ab, " profile=");
			audit_log_untrustedstring(ab, profile->base.hname);
		} else {
			audit_log_format(ab, " label=");
			aa_label_xaudit(ab, root_ns, label, FLAG_VIEW_SUBNS,
					GFP_ATOMIC);
		}
	}

	if (aad(sa)->name) {
		audit_log_format(ab, " name=");
		audit_log_untrustedstring(ab, aad(sa)->name);
	}
}