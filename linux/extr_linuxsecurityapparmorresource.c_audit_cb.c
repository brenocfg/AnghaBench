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
struct TYPE_3__ {size_t rlim; int /*<<< orphan*/  max; } ;
struct TYPE_4__ {scalar_t__ peer; int /*<<< orphan*/  label; TYPE_1__ rlim; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAGS_NONE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  aa_label_xaudit (struct audit_buffer*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* aad (struct common_audit_data*) ; 
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*,...) ; 
 int /*<<< orphan*/  labels_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rlim_names ; 

__attribute__((used)) static void audit_cb(struct audit_buffer *ab, void *va)
{
	struct common_audit_data *sa = va;

	audit_log_format(ab, " rlimit=%s value=%lu",
			 rlim_names[aad(sa)->rlim.rlim], aad(sa)->rlim.max);
	if (aad(sa)->peer) {
		audit_log_format(ab, " peer=");
		aa_label_xaudit(ab, labels_ns(aad(sa)->label), aad(sa)->peer,
				FLAGS_NONE, GFP_ATOMIC);
	}
}