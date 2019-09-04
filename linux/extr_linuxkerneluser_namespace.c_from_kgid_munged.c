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
struct user_namespace {int dummy; } ;
typedef  int /*<<< orphan*/  kgid_t ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 scalar_t__ from_kgid (struct user_namespace*,int /*<<< orphan*/ ) ; 
 scalar_t__ overflowgid ; 

gid_t from_kgid_munged(struct user_namespace *targ, kgid_t kgid)
{
	gid_t gid;
	gid = from_kgid(targ, kgid);

	if (gid == (gid_t) -1)
		gid = overflowgid;
	return gid;
}