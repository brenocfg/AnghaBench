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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct selinux_state {TYPE_1__* ss; } ;
struct TYPE_2__ {int /*<<< orphan*/  policy_rwlock; } ;

/* Variables and functions */
 int __security_genfs_sid (struct selinux_state*,char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

int security_genfs_sid(struct selinux_state *state,
		       const char *fstype,
		       char *path,
		       u16 orig_sclass,
		       u32 *sid)
{
	int retval;

	read_lock(&state->ss->policy_rwlock);
	retval = __security_genfs_sid(state, fstype, path, orig_sclass, sid);
	read_unlock(&state->ss->policy_rwlock);
	return retval;
}