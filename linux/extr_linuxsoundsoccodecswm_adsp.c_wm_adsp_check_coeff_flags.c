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
struct wm_coeff_parsed_coeff {unsigned int flags; int /*<<< orphan*/  ctl_type; } ;
struct wm_adsp {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  adsp_err (struct wm_adsp*,char*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm_adsp_check_coeff_flags(struct wm_adsp *dsp,
				const struct wm_coeff_parsed_coeff *coeff_blk,
				unsigned int f_required,
				unsigned int f_illegal)
{
	if ((coeff_blk->flags & f_illegal) ||
	    ((coeff_blk->flags & f_required) != f_required)) {
		adsp_err(dsp, "Illegal flags 0x%x for control type 0x%x\n",
			 coeff_blk->flags, coeff_blk->ctl_type);
		return -EINVAL;
	}

	return 0;
}