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
struct se_lun {int lun_tg_pt_secondary_stat; } ;
typedef  int ssize_t ;

/* Variables and functions */
 unsigned long ALUA_STATUS_ALTERED_BY_EXPLICIT_STPG ; 
 unsigned long ALUA_STATUS_ALTERED_BY_IMPLICIT_ALUA ; 
 unsigned long ALUA_STATUS_NONE ; 
 int EINVAL ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

ssize_t core_alua_store_secondary_status(
	struct se_lun *lun,
	const char *page,
	size_t count)
{
	unsigned long tmp;
	int ret;

	ret = kstrtoul(page, 0, &tmp);
	if (ret < 0) {
		pr_err("Unable to extract alua_tg_pt_status\n");
		return ret;
	}
	if ((tmp != ALUA_STATUS_NONE) &&
	    (tmp != ALUA_STATUS_ALTERED_BY_EXPLICIT_STPG) &&
	    (tmp != ALUA_STATUS_ALTERED_BY_IMPLICIT_ALUA)) {
		pr_err("Illegal value for alua_tg_pt_status: %lu\n",
				tmp);
		return -EINVAL;
	}
	lun->lun_tg_pt_secondary_stat = (int)tmp;

	return count;
}