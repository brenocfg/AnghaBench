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
typedef  scalar_t__ uid_t ;
struct user_namespace {int dummy; } ;
typedef  int /*<<< orphan*/  kuid_t ;

/* Variables and functions */
 scalar_t__ from_kuid (struct user_namespace*,int /*<<< orphan*/ ) ; 
 scalar_t__ overflowuid ; 

uid_t from_kuid_munged(struct user_namespace *targ, kuid_t kuid)
{
	uid_t uid;
	uid = from_kuid(targ, kuid);

	if (uid == (uid_t) -1)
		uid = overflowuid;
	return uid;
}