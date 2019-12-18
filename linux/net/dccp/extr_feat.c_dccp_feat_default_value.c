#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int default_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCCP_BUG_ON (int) ; 
 int dccp_feat_index (int /*<<< orphan*/ ) ; 
 TYPE_1__* dccp_feat_table ; 

__attribute__((used)) static int dccp_feat_default_value(u8 feat_num)
{
	int idx = dccp_feat_index(feat_num);
	/*
	 * There are no default values for unknown features, so encountering a
	 * negative index here indicates a serious problem somewhere else.
	 */
	DCCP_BUG_ON(idx < 0);

	return idx < 0 ? 0 : dccp_feat_table[idx].default_value;
}