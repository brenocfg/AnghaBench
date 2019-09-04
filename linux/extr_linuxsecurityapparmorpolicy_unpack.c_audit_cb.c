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
struct TYPE_3__ {scalar_t__ pos; scalar_t__ ns; } ;
struct TYPE_4__ {TYPE_1__ iface; scalar_t__ name; } ;

/* Variables and functions */
 TYPE_2__* aad (struct common_audit_data*) ; 
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*,...) ; 
 int /*<<< orphan*/  audit_log_untrustedstring (struct audit_buffer*,scalar_t__) ; 

__attribute__((used)) static void audit_cb(struct audit_buffer *ab, void *va)
{
	struct common_audit_data *sa = va;

	if (aad(sa)->iface.ns) {
		audit_log_format(ab, " ns=");
		audit_log_untrustedstring(ab, aad(sa)->iface.ns);
	}
	if (aad(sa)->name) {
		audit_log_format(ab, " name=");
		audit_log_untrustedstring(ab, aad(sa)->name);
	}
	if (aad(sa)->iface.pos)
		audit_log_format(ab, " offset=%ld", aad(sa)->iface.pos);
}