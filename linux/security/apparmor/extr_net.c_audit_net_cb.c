#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* net; } ;
struct common_audit_data {TYPE_2__ u; } ;
struct audit_buffer {int dummy; } ;
struct TYPE_7__ {size_t type; int /*<<< orphan*/  protocol; } ;
struct TYPE_8__ {int request; int denied; scalar_t__ peer; int /*<<< orphan*/  label; TYPE_3__ net; } ;
struct TYPE_5__ {size_t family; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAGS_NONE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int NET_PERMS_MASK ; 
 int /*<<< orphan*/  aa_audit_perm_mask (struct audit_buffer*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  aa_label_xaudit (struct audit_buffer*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* aad (struct common_audit_data*) ; 
 scalar_t__* address_family_names ; 
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*,...) ; 
 int /*<<< orphan*/  audit_log_string (struct audit_buffer*,scalar_t__) ; 
 int /*<<< orphan*/  labels_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_mask_names ; 
 scalar_t__* sock_type_names ; 

void audit_net_cb(struct audit_buffer *ab, void *va)
{
	struct common_audit_data *sa = va;

	audit_log_format(ab, " family=");
	if (address_family_names[sa->u.net->family])
		audit_log_string(ab, address_family_names[sa->u.net->family]);
	else
		audit_log_format(ab, "\"unknown(%d)\"", sa->u.net->family);
	audit_log_format(ab, " sock_type=");
	if (sock_type_names[aad(sa)->net.type])
		audit_log_string(ab, sock_type_names[aad(sa)->net.type]);
	else
		audit_log_format(ab, "\"unknown(%d)\"", aad(sa)->net.type);
	audit_log_format(ab, " protocol=%d", aad(sa)->net.protocol);

	if (aad(sa)->request & NET_PERMS_MASK) {
		audit_log_format(ab, " requested_mask=");
		aa_audit_perm_mask(ab, aad(sa)->request, NULL, 0,
				   net_mask_names, NET_PERMS_MASK);

		if (aad(sa)->denied & NET_PERMS_MASK) {
			audit_log_format(ab, " denied_mask=");
			aa_audit_perm_mask(ab, aad(sa)->denied, NULL, 0,
					   net_mask_names, NET_PERMS_MASK);
		}
	}
	if (aad(sa)->peer) {
		audit_log_format(ab, " peer=");
		aa_label_xaudit(ab, labels_ns(aad(sa)->label), aad(sa)->peer,
				FLAGS_NONE, GFP_ATOMIC);
	}
}