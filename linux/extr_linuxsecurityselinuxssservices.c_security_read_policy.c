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
struct selinux_state {TYPE_1__* ss; int /*<<< orphan*/  initialized; } ;
struct policydb {int dummy; } ;
struct policy_file {size_t len; void* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  policy_rwlock; struct policydb policydb; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int policydb_write (struct policydb*,struct policy_file*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 size_t security_policydb_len (struct selinux_state*) ; 
 void* vmalloc_user (size_t) ; 

int security_read_policy(struct selinux_state *state,
			 void **data, size_t *len)
{
	struct policydb *policydb = &state->ss->policydb;
	int rc;
	struct policy_file fp;

	if (!state->initialized)
		return -EINVAL;

	*len = security_policydb_len(state);

	*data = vmalloc_user(*len);
	if (!*data)
		return -ENOMEM;

	fp.data = *data;
	fp.len = *len;

	read_lock(&state->ss->policy_rwlock);
	rc = policydb_write(policydb, &fp);
	read_unlock(&state->ss->policy_rwlock);

	if (rc)
		return rc;

	*len = (unsigned long)fp.data - (unsigned long)*data;
	return 0;

}