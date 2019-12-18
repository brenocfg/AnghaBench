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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct tc_skbedit {int dummy; } ;
struct tc_action {int dummy; } ;

/* Variables and functions */
 size_t nla_total_size (int) ; 
 size_t nla_total_size_64bit (int) ; 

__attribute__((used)) static size_t tcf_skbedit_get_fill_size(const struct tc_action *act)
{
	return nla_total_size(sizeof(struct tc_skbedit))
		+ nla_total_size(sizeof(u32)) /* TCA_SKBEDIT_PRIORITY */
		+ nla_total_size(sizeof(u16)) /* TCA_SKBEDIT_QUEUE_MAPPING */
		+ nla_total_size(sizeof(u32)) /* TCA_SKBEDIT_MARK */
		+ nla_total_size(sizeof(u16)) /* TCA_SKBEDIT_PTYPE */
		+ nla_total_size(sizeof(u32)) /* TCA_SKBEDIT_MASK */
		+ nla_total_size_64bit(sizeof(u64)); /* TCA_SKBEDIT_FLAGS */
}