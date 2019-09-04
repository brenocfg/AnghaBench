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
 int gid_valid (int /*<<< orphan*/ ) ; 
 int projid_valid (int /*<<< orphan*/ ) ; 
 int uid_valid (int /*<<< orphan*/ ) ; 

bool qid_valid(struct kqid qid)
{
	switch (qid.type) {
	case USRQUOTA:
		return uid_valid(qid.uid);
	case GRPQUOTA:
		return gid_valid(qid.gid);
	case PRJQUOTA:
		return projid_valid(qid.projid);
	default:
		BUG();
	}
}