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
struct ima_template_desc {int dummy; } ;
struct cred {int dummy; } ;
typedef  enum ima_hooks { ____Placeholder_ima_hooks } ima_hooks ;

/* Variables and functions */
 int IMA_APPRAISE ; 
 int IMA_AUDIT ; 
 int IMA_HASH ; 
 int IMA_MEASURE ; 
 int ima_match_policy (struct inode*,struct cred const*,int /*<<< orphan*/ ,int,int,int,int*,struct ima_template_desc**) ; 
 int ima_policy_flag ; 

int ima_get_action(struct inode *inode, const struct cred *cred, u32 secid,
		   int mask, enum ima_hooks func, int *pcr,
		   struct ima_template_desc **template_desc)
{
	int flags = IMA_MEASURE | IMA_AUDIT | IMA_APPRAISE | IMA_HASH;

	flags &= ima_policy_flag;

	return ima_match_policy(inode, cred, secid, func, mask, flags, pcr,
				template_desc);
}