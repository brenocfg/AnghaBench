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
struct TYPE_4__ {scalar_t__ reset_clamp_val; scalar_t__ ob_v_sz_calc; scalar_t__ ob_start_h; scalar_t__ ob_start_v; } ;
struct TYPE_3__ {int clamp_pix_limit; int win_count_calc; scalar_t__ win_start_h_calc; scalar_t__ win_start_v_calc; } ;
struct vpfe_isif_black_clamp {scalar_t__ dc_offset; TYPE_2__ vert; TYPE_1__ horz; int /*<<< orphan*/  en; } ;

/* Variables and functions */
 scalar_t__ DM365_ISIF_MAX_CLDC ; 
 scalar_t__ DM365_ISIF_MAX_CLHSH ; 
 scalar_t__ DM365_ISIF_MAX_CLHSV ; 
 scalar_t__ DM365_ISIF_MAX_CLVRV ; 
 scalar_t__ DM365_ISIF_MAX_CLVSH ; 
 scalar_t__ DM365_ISIF_MAX_CLVSV ; 
 scalar_t__ DM365_ISIF_MAX_HEIGHT_BLACK_REGION ; 
 int EINVAL ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int isif_validate_bclamp_params(struct vpfe_isif_black_clamp *bclamp)
{
	int err = -EINVAL;

	if (bclamp->dc_offset > DM365_ISIF_MAX_CLDC) {
		pr_err("Invalid bclamp dc_offset value\n");
		return err;
	}
	if (!bclamp->en)
		return 0;
	if (bclamp->horz.clamp_pix_limit > 1) {
		pr_err("Invalid bclamp horz clamp_pix_limit value\n");
		return err;
	}
	if (bclamp->horz.win_count_calc < 1 ||
			bclamp->horz.win_count_calc > 32) {
		pr_err("Invalid bclamp horz win_count_calc value\n");
		return err;
	}
	if (bclamp->horz.win_start_h_calc > DM365_ISIF_MAX_CLHSH) {
		pr_err("Invalid bclamp win_start_v_calc value\n");
		return err;
	}

	if (bclamp->horz.win_start_v_calc > DM365_ISIF_MAX_CLHSV) {
		pr_err("Invalid bclamp win_start_v_calc value\n");
		return err;
	}
	if (bclamp->vert.reset_clamp_val > DM365_ISIF_MAX_CLVRV) {
		pr_err("Invalid bclamp reset_clamp_val value\n");
		return err;
	}
	if (bclamp->vert.ob_v_sz_calc > DM365_ISIF_MAX_HEIGHT_BLACK_REGION) {
		pr_err("Invalid bclamp ob_v_sz_calc value\n");
		return err;
	}
	if (bclamp->vert.ob_start_h > DM365_ISIF_MAX_CLVSH) {
		pr_err("Invalid bclamp ob_start_h value\n");
		return err;
	}
	if (bclamp->vert.ob_start_v > DM365_ISIF_MAX_CLVSV) {
		pr_err("Invalid bclamp ob_start_h value\n");
		return err;
	}
	return 0;
}