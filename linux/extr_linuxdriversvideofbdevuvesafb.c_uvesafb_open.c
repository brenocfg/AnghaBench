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
struct uvesafb_par {int /*<<< orphan*/  ref_count; int /*<<< orphan*/ * vbe_state_orig; scalar_t__ vbe_state_size; } ;
struct fb_info {struct uvesafb_par* par; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * uvesafb_vbe_state_save (struct uvesafb_par*) ; 

__attribute__((used)) static int uvesafb_open(struct fb_info *info, int user)
{
	struct uvesafb_par *par = info->par;
	int cnt = atomic_read(&par->ref_count);
	u8 *buf = NULL;

	if (!cnt && par->vbe_state_size) {
		buf =  uvesafb_vbe_state_save(par);
		if (IS_ERR(buf)) {
			pr_warn("save hardware state failed, error code is %ld!\n",
				PTR_ERR(buf));
		} else {
			par->vbe_state_orig = buf;
		}
	}

	atomic_inc(&par->ref_count);
	return 0;
}