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
struct TYPE_2__ {int /*<<< orphan*/  fE; int /*<<< orphan*/  inheritable; int /*<<< orphan*/  permitted; } ;
struct audit_names {int /*<<< orphan*/  fcap_ver; TYPE_1__ fcap; } ;
struct audit_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  audit_log_cap (struct audit_buffer*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void audit_log_fcaps(struct audit_buffer *ab, struct audit_names *name)
{
	audit_log_cap(ab, "cap_fp", &name->fcap.permitted);
	audit_log_cap(ab, "cap_fi", &name->fcap.inheritable);
	audit_log_format(ab, " cap_fe=%d cap_fver=%x",
			 name->fcap.fE, name->fcap_ver);
}