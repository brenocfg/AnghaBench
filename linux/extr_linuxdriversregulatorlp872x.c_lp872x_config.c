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
struct lp872x_platform_data {int /*<<< orphan*/  general_config; int /*<<< orphan*/  update_config; } ;
struct lp872x {struct lp872x_platform_data* pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  LP872X_GENERAL_CFG ; 
 int lp872x_init_dvs (struct lp872x*) ; 
 int lp872x_write_byte (struct lp872x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lp872x_config(struct lp872x *lp)
{
	struct lp872x_platform_data *pdata = lp->pdata;
	int ret;

	if (!pdata || !pdata->update_config)
		goto init_dvs;

	ret = lp872x_write_byte(lp, LP872X_GENERAL_CFG, pdata->general_config);
	if (ret)
		return ret;

init_dvs:
	return lp872x_init_dvs(lp);
}