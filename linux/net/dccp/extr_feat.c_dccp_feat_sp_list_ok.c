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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  dccp_feat_is_valid_sp_val (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 dccp_feat_sp_list_ok(u8 feat_num, u8 const *sp_list, u8 sp_len)
{
	if (sp_list == NULL || sp_len < 1)
		return 0;
	while (sp_len--)
		if (!dccp_feat_is_valid_sp_val(feat_num, *sp_list++))
			return 0;
	return 1;
}