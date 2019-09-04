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
struct audit_context {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static inline int security_filter_rule_match(u32 secid, u32 field, u32 op,
					     void *lsmrule,
					     struct audit_context *actx)
{
	return -EINVAL;
}