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
struct ocfs2_quota_recovery {int /*<<< orphan*/ * r_list; } ;

/* Variables and functions */
 int OCFS2_MAXQUOTAS ; 
 int /*<<< orphan*/  free_recovery_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ocfs2_quota_recovery*) ; 

void ocfs2_free_quota_recovery(struct ocfs2_quota_recovery *rec)
{
	int type;

	for (type = 0; type < OCFS2_MAXQUOTAS; type++)
		free_recovery_list(&(rec->r_list[type]));
	kfree(rec);
}