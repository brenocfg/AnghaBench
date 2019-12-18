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
struct nd_cmd_ars_status {int dummy; } ;
struct nd_cmd_ars_cap {int max_ars_out; int status; int /*<<< orphan*/  clear_err_unit; } ;
struct nd_ars_record {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ND_ARS_PERSISTENT ; 
 int ND_ARS_VOLATILE ; 
 int /*<<< orphan*/  NFIT_TEST_CLEAR_ERR_UNIT ; 
 int SZ_4K ; 

__attribute__((used)) static int nfit_test_cmd_ars_cap(struct nd_cmd_ars_cap *nd_cmd,
		unsigned int buf_len)
{
	int ars_recs;

	if (buf_len < sizeof(*nd_cmd))
		return -EINVAL;

	/* for testing, only store up to n records that fit within 4k */
	ars_recs = SZ_4K / sizeof(struct nd_ars_record);

	nd_cmd->max_ars_out = sizeof(struct nd_cmd_ars_status)
		+ ars_recs * sizeof(struct nd_ars_record);
	nd_cmd->status = (ND_ARS_PERSISTENT | ND_ARS_VOLATILE) << 16;
	nd_cmd->clear_err_unit = NFIT_TEST_CLEAR_ERR_UNIT;

	return 0;
}