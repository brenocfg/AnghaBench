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
struct kqid {int type; int /*<<< orphan*/  projid; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
typedef  int /*<<< orphan*/  qid_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  GRPQUOTA 130 
#define  PRJQUOTA 129 
#define  USRQUOTA 128 
 int /*<<< orphan*/  from_kgid_munged (struct user_namespace*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_kprojid_munged (struct user_namespace*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_kuid_munged (struct user_namespace*,int /*<<< orphan*/ ) ; 

qid_t from_kqid_munged(struct user_namespace *targ, struct kqid kqid)
{
	switch (kqid.type) {
	case USRQUOTA:
		return from_kuid_munged(targ, kqid.uid);
	case GRPQUOTA:
		return from_kgid_munged(targ, kqid.gid);
	case PRJQUOTA:
		return from_kprojid_munged(targ, kqid.projid);
	default:
		BUG();
	}
}