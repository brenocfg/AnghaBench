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
struct nfit_test {int /*<<< orphan*/  work; int /*<<< orphan*/  badrange; } ;
struct nd_cmd_ars_err_inj {scalar_t__ err_inj_spa_range_length; int err_inj_options; scalar_t__ status; int /*<<< orphan*/  err_inj_spa_range_base; } ;

/* Variables and functions */
 int EINVAL ; 
 int ND_ARS_ERR_INJ_OPT_NOTIFY ; 
 scalar_t__ NFIT_ARS_INJECT_INVALID ; 
 int badrange_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  nfit_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfit_test_cmd_ars_error_inject(struct nfit_test *t,
		struct nd_cmd_ars_err_inj *err_inj, unsigned int buf_len)
{
	int rc;

	if (buf_len != sizeof(*err_inj)) {
		rc = -EINVAL;
		goto err;
	}

	if (err_inj->err_inj_spa_range_length <= 0) {
		rc = -EINVAL;
		goto err;
	}

	rc =  badrange_add(&t->badrange, err_inj->err_inj_spa_range_base,
			err_inj->err_inj_spa_range_length);
	if (rc < 0)
		goto err;

	if (err_inj->err_inj_options & (1 << ND_ARS_ERR_INJ_OPT_NOTIFY))
		queue_work(nfit_wq, &t->work);

	err_inj->status = 0;
	return 0;

err:
	err_inj->status = NFIT_ARS_INJECT_INVALID;
	return rc;
}