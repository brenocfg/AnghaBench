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
struct vpfe_isif_raw_config {int /*<<< orphan*/  bclamp; int /*<<< orphan*/  dfc; int /*<<< orphan*/  df_csc; } ;

/* Variables and functions */
 int isif_validate_bclamp_params (int /*<<< orphan*/ *) ; 
 int isif_validate_df_csc_params (int /*<<< orphan*/ *) ; 
 int isif_validate_dfc_params (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
isif_validate_raw_params(struct vpfe_isif_raw_config *params)
{
	int ret;

	ret = isif_validate_df_csc_params(&params->df_csc);
	if (ret)
		return ret;
	ret = isif_validate_dfc_params(&params->dfc);
	if (ret)
		return ret;
	return isif_validate_bclamp_params(&params->bclamp);
}