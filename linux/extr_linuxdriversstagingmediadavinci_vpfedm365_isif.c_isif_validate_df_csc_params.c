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
struct vpfe_isif_color_space_conv {TYPE_1__* coeff; scalar_t__ en; } ;
struct vpfe_isif_df_csc {scalar_t__ start_pix; scalar_t__ num_pixels; scalar_t__ start_line; scalar_t__ num_lines; struct vpfe_isif_color_space_conv csc; int /*<<< orphan*/  df_or_csc; } ;
struct TYPE_2__ {scalar_t__ integer; scalar_t__ decimal; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ISIF_CSC_COEF_DECIMAL_MASK ; 
 scalar_t__ ISIF_CSC_COEF_INTEG_MASK ; 
 scalar_t__ ISIF_DF_CSC_LNH_MASK ; 
 scalar_t__ ISIF_DF_CSC_SPH_MASK ; 
 scalar_t__ ISIF_DF_NUMLINES ; 
 scalar_t__ ISIF_DF_NUMPIX ; 
 int VPFE_ISIF_CSC_NUM_COEFF ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int isif_validate_df_csc_params(struct vpfe_isif_df_csc *df_csc)
{
	struct vpfe_isif_color_space_conv *csc;
	int err = -EINVAL;
	int i;

	if (!df_csc->df_or_csc) {
		/* csc configuration */
		csc = &df_csc->csc;
		if (csc->en) {
			for (i = 0; i < VPFE_ISIF_CSC_NUM_COEFF; i++)
				if (csc->coeff[i].integer >
				    ISIF_CSC_COEF_INTEG_MASK ||
				    csc->coeff[i].decimal >
				    ISIF_CSC_COEF_DECIMAL_MASK) {
					pr_err("Invalid CSC coefficients\n");
					return err;
				}
		}
	}
	if (df_csc->start_pix > ISIF_DF_CSC_SPH_MASK) {
		pr_err("Invalid df_csc start pix value\n");
		return err;
	}

	if (df_csc->num_pixels > ISIF_DF_NUMPIX) {
		pr_err("Invalid df_csc num pixels value\n");
		return err;
	}

	if (df_csc->start_line > ISIF_DF_CSC_LNH_MASK) {
		pr_err("Invalid df_csc start_line value\n");
		return err;
	}

	if (df_csc->num_lines > ISIF_DF_NUMLINES) {
		pr_err("Invalid df_csc num_lines value\n");
		return err;
	}

	return 0;
}