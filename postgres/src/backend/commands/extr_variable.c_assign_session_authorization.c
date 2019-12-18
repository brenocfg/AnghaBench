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
struct TYPE_2__ {int /*<<< orphan*/  is_superuser; int /*<<< orphan*/  roleid; } ;
typedef  TYPE_1__ role_auth_extra ;

/* Variables and functions */
 int /*<<< orphan*/  SetSessionAuthorization (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
assign_session_authorization(const char *newval, void *extra)
{
	role_auth_extra *myextra = (role_auth_extra *) extra;

	/* Do nothing for the boot_val default of NULL */
	if (!myextra)
		return;

	SetSessionAuthorization(myextra->roleid, myextra->is_superuser);
}