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
struct hlist_head {int dummy; } ;
struct dquot {int /*<<< orphan*/  dq_hash; int /*<<< orphan*/  dq_id; int /*<<< orphan*/  dq_sb; } ;

/* Variables and functions */
 struct hlist_head* dquot_hash ; 
 int hashfn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,struct hlist_head*) ; 

__attribute__((used)) static inline void insert_dquot_hash(struct dquot *dquot)
{
	struct hlist_head *head;
	head = dquot_hash + hashfn(dquot->dq_sb, dquot->dq_id);
	hlist_add_head(&dquot->dq_hash, head);
}