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
typedef  int /*<<< orphan*/  u32 ;
struct inode {int dummy; } ;
typedef  enum ima_hooks { ____Placeholder_ima_hooks } ima_hooks ;

/* Variables and functions */
 int IMA_APPRAISE ; 
 int IMA_HASH ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  current_cred () ; 
 int /*<<< orphan*/  ima_appraise ; 
 int ima_match_policy (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  security_task_getsecid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ima_must_appraise(struct inode *inode, int mask, enum ima_hooks func)
{
	u32 secid;

	if (!ima_appraise)
		return 0;

	security_task_getsecid(current, &secid);
	return ima_match_policy(inode, current_cred(), secid, func, mask,
				IMA_APPRAISE | IMA_HASH, NULL, NULL);
}