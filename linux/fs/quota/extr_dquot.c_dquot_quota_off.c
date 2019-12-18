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
struct super_block {int dummy; } ;

/* Variables and functions */
 int DQUOT_LIMITS_ENABLED ; 
 int DQUOT_USAGE_ENABLED ; 
 int dquot_disable (struct super_block*,int,int) ; 

int dquot_quota_off(struct super_block *sb, int type)
{
	return dquot_disable(sb, type,
			     DQUOT_USAGE_ENABLED | DQUOT_LIMITS_ENABLED);
}