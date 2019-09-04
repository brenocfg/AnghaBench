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
struct qtree_mem_dqinfo {int dummy; } ;
struct kqid {int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  qid_t ;

/* Variables and functions */
 int /*<<< orphan*/  QT_TREEOFF ; 
 int find_next_id (struct qtree_mem_dqinfo*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_kqid (int /*<<< orphan*/ *,struct kqid) ; 
 int /*<<< orphan*/  init_user_ns ; 
 struct kqid make_kqid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int qtree_get_next_id(struct qtree_mem_dqinfo *info, struct kqid *qid)
{
	qid_t id = from_kqid(&init_user_ns, *qid);
	int ret;

	ret = find_next_id(info, &id, QT_TREEOFF, 0);
	if (ret < 0)
		return ret;
	*qid = make_kqid(&init_user_ns, qid->type, id);
	return 0;
}