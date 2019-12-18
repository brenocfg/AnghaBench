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
typedef  int u32 ;
struct aa_label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int FLAG_ABS_ROOT ; 
 int FLAG_HIDDEN_UNCONFINED ; 
 int FLAG_SHOW_MODE ; 
 int FLAG_VIEW_SUBNS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int aa_label_asxprint (char**,int /*<<< orphan*/ ,struct aa_label*,int,int /*<<< orphan*/ ) ; 
 int aa_label_snxprint (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct aa_label*,int) ; 
 struct aa_label* aa_secid_to_label (int) ; 
 int /*<<< orphan*/  root_ns ; 

int apparmor_secid_to_secctx(u32 secid, char **secdata, u32 *seclen)
{
	/* TODO: cache secctx and ref count so we don't have to recreate */
	struct aa_label *label = aa_secid_to_label(secid);
	int len;

	AA_BUG(!seclen);

	if (!label)
		return -EINVAL;

	if (secdata)
		len = aa_label_asxprint(secdata, root_ns, label,
					FLAG_SHOW_MODE | FLAG_VIEW_SUBNS |
					FLAG_HIDDEN_UNCONFINED | FLAG_ABS_ROOT,
					GFP_ATOMIC);
	else
		len = aa_label_snxprint(NULL, 0, root_ns, label,
					FLAG_SHOW_MODE | FLAG_VIEW_SUBNS |
					FLAG_HIDDEN_UNCONFINED | FLAG_ABS_ROOT);
	if (len < 0)
		return -ENOMEM;

	*seclen = len;

	return 0;
}