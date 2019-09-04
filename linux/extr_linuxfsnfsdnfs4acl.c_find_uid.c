#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  deny; int /*<<< orphan*/  allow; } ;
struct posix_acl_state {TYPE_3__ everyone; struct posix_ace_state_array* users; } ;
struct posix_ace_state_array {int n; TYPE_2__* aces; } ;
typedef  int /*<<< orphan*/  kuid_t ;
struct TYPE_4__ {int /*<<< orphan*/  deny; int /*<<< orphan*/  allow; } ;
struct TYPE_5__ {TYPE_1__ perms; int /*<<< orphan*/  uid; } ;

/* Variables and functions */
 scalar_t__ uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int find_uid(struct posix_acl_state *state, kuid_t uid)
{
	struct posix_ace_state_array *a = state->users;
	int i;

	for (i = 0; i < a->n; i++)
		if (uid_eq(a->aces[i].uid, uid))
			return i;
	/* Not found: */
	a->n++;
	a->aces[i].uid = uid;
	a->aces[i].perms.allow = state->everyone.allow;
	a->aces[i].perms.deny  = state->everyone.deny;

	return i;
}