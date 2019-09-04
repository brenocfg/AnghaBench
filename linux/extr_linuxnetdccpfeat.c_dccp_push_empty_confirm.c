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
typedef  int /*<<< orphan*/  u8 ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int dccp_feat_push_confirm (struct list_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dccp_push_empty_confirm(struct list_head *fn_list, u8 feat, u8 local)
{
	return dccp_feat_push_confirm(fn_list, feat, local, NULL);
}