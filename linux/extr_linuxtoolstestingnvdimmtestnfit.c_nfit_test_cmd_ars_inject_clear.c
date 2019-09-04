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
struct nfit_test {int /*<<< orphan*/  badrange; } ;
struct nd_cmd_ars_err_inj_clr {scalar_t__ err_inj_clr_spa_range_length; scalar_t__ status; int /*<<< orphan*/  err_inj_clr_spa_range_base; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ NFIT_ARS_INJECT_INVALID ; 
 int /*<<< orphan*/  badrange_forget (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int nfit_test_cmd_ars_inject_clear(struct nfit_test *t,
		struct nd_cmd_ars_err_inj_clr *err_clr, unsigned int buf_len)
{
	int rc;

	if (buf_len != sizeof(*err_clr)) {
		rc = -EINVAL;
		goto err;
	}

	if (err_clr->err_inj_clr_spa_range_length <= 0) {
		rc = -EINVAL;
		goto err;
	}

	badrange_forget(&t->badrange, err_clr->err_inj_clr_spa_range_base,
			err_clr->err_inj_clr_spa_range_length);

	err_clr->status = 0;
	return 0;

err:
	err_clr->status = NFIT_ARS_INJECT_INVALID;
	return rc;
}