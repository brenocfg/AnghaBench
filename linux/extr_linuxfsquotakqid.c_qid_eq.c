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
struct kqid {int type; int /*<<< orphan*/  projid; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  GRPQUOTA 130 
#define  PRJQUOTA 129 
#define  USRQUOTA 128 
 int gid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int projid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool qid_eq(struct kqid left, struct kqid right)
{
	if (left.type != right.type)
		return false;
	switch(left.type) {
	case USRQUOTA:
		return uid_eq(left.uid, right.uid);
	case GRPQUOTA:
		return gid_eq(left.gid, right.gid);
	case PRJQUOTA:
		return projid_eq(left.projid, right.projid);
	default:
		BUG();
	}
}