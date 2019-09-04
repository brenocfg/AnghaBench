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
typedef  int /*<<< orphan*/  u32 ;
struct aa_label {int /*<<< orphan*/  secid; } ;
struct TYPE_4__ {TYPE_1__* unconfined; } ;
struct TYPE_3__ {int /*<<< orphan*/  label; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct aa_label*) ; 
 int PTR_ERR (struct aa_label*) ; 
 struct aa_label* aa_label_strn_parse (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 TYPE_2__* root_ns ; 

int apparmor_secctx_to_secid(const char *secdata, u32 seclen, u32 *secid)
{
	struct aa_label *label;

	label = aa_label_strn_parse(&root_ns->unconfined->label, secdata,
				    seclen, GFP_KERNEL, false, false);
	if (IS_ERR(label))
		return PTR_ERR(label);
	*secid = label->secid;

	return 0;
}