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
struct TYPE_2__ {int type; } ;

/* Variables and functions */
 TYPE_1__* aad (struct common_audit_data*) ; 
 int /*<<< orphan*/  audit_pre ; 
 int /*<<< orphan*/  common_lsm_audit (struct common_audit_data*,int /*<<< orphan*/ ,void (*) (struct audit_buffer*,void*)) ; 

void aa_audit_msg(int type, struct common_audit_data *sa,
		  void (*cb) (struct audit_buffer *, void *))
{
	aad(sa)->type = type;
	common_lsm_audit(sa, audit_pre, cb);
}