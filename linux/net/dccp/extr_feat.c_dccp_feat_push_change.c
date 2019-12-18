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
typedef  void* u8 ;
struct list_head {int dummy; } ;
struct dccp_feat_entry {int needs_confirm; int empty_confirm; void* needs_mandatory; int /*<<< orphan*/  val; int /*<<< orphan*/  state; void* is_local; void* feat_num; } ;
typedef  int /*<<< orphan*/  dccp_feat_val ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FEAT_INITIALISING ; 
 struct dccp_feat_entry* dccp_feat_entry_new (struct list_head*,void*,void*) ; 

__attribute__((used)) static int dccp_feat_push_change(struct list_head *fn_list, u8 feat, u8 local,
				 u8 mandatory, dccp_feat_val *fval)
{
	struct dccp_feat_entry *new = dccp_feat_entry_new(fn_list, feat, local);

	if (new == NULL)
		return -ENOMEM;

	new->feat_num	     = feat;
	new->is_local	     = local;
	new->state	     = FEAT_INITIALISING;
	new->needs_confirm   = false;
	new->empty_confirm   = false;
	new->val	     = *fval;
	new->needs_mandatory = mandatory;

	return 0;
}