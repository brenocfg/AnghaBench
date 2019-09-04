#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  vec; } ;
struct TYPE_4__ {TYPE_1__ sp; } ;
struct dccp_feat_entry {TYPE_2__ val; int /*<<< orphan*/  feat_num; } ;

/* Variables and functions */
 scalar_t__ FEAT_SP ; 
 scalar_t__ FEAT_UNKNOWN ; 
 scalar_t__ dccp_feat_clone_sp_val (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dccp_feat_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfp_any () ; 
 int /*<<< orphan*/  kfree (struct dccp_feat_entry*) ; 
 struct dccp_feat_entry* kmemdup (struct dccp_feat_entry const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dccp_feat_entry *
	      dccp_feat_clone_entry(struct dccp_feat_entry const *original)
{
	struct dccp_feat_entry *new;
	u8 type = dccp_feat_type(original->feat_num);

	if (type == FEAT_UNKNOWN)
		return NULL;

	new = kmemdup(original, sizeof(struct dccp_feat_entry), gfp_any());
	if (new == NULL)
		return NULL;

	if (type == FEAT_SP && dccp_feat_clone_sp_val(&new->val,
						      original->val.sp.vec,
						      original->val.sp.len)) {
		kfree(new);
		return NULL;
	}
	return new;
}