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
struct kqid {int dummy; } ;
typedef  int /*<<< orphan*/  qid_t ;

/* Variables and functions */
 int __get_index (struct qtree_mem_dqinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  from_kqid (int /*<<< orphan*/ *,struct kqid) ; 
 int /*<<< orphan*/  init_user_ns ; 

__attribute__((used)) static int get_index(struct qtree_mem_dqinfo *info, struct kqid qid, int depth)
{
	qid_t id = from_kqid(&init_user_ns, qid);

	return __get_index(info, id, depth);
}