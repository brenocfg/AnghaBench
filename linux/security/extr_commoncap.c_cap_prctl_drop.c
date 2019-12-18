#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cred {int /*<<< orphan*/  cap_bset; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SETPCAP ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  cap_lower (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  cap_valid (unsigned long) ; 
 int commit_creds (struct cred*) ; 
 int /*<<< orphan*/  current_user_ns () ; 
 int /*<<< orphan*/  ns_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cred* prepare_creds () ; 

__attribute__((used)) static int cap_prctl_drop(unsigned long cap)
{
	struct cred *new;

	if (!ns_capable(current_user_ns(), CAP_SETPCAP))
		return -EPERM;
	if (!cap_valid(cap))
		return -EINVAL;

	new = prepare_creds();
	if (!new)
		return -ENOMEM;
	cap_lower(new->cap_bset, cap);
	return commit_creds(new);
}