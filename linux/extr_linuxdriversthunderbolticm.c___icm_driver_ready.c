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
typedef  int /*<<< orphan*/  u32 ;
struct tb_cfg_result {int /*<<< orphan*/  err; } ;
struct tb {int /*<<< orphan*/  ctl; } ;
struct icm {int (* driver_ready ) (struct tb*,int*,size_t*,int*) ;} ;
typedef  enum tb_security_level { ____Placeholder_tb_security_level } tb_security_level ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  TB_CFG_SWITCH ; 
 int /*<<< orphan*/  msleep (int) ; 
 int stub1 (struct tb*,int*,size_t*,int*) ; 
 struct tb_cfg_result tb_cfg_read_raw (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  tb_err (struct tb*,char*) ; 
 struct icm* tb_priv (struct tb*) ; 

__attribute__((used)) static int
__icm_driver_ready(struct tb *tb, enum tb_security_level *security_level,
		   size_t *nboot_acl, bool *rpm)
{
	struct icm *icm = tb_priv(tb);
	unsigned int retries = 50;
	int ret;

	ret = icm->driver_ready(tb, security_level, nboot_acl, rpm);
	if (ret) {
		tb_err(tb, "failed to send driver ready to ICM\n");
		return ret;
	}

	/*
	 * Hold on here until the switch config space is accessible so
	 * that we can read root switch config successfully.
	 */
	do {
		struct tb_cfg_result res;
		u32 tmp;

		res = tb_cfg_read_raw(tb->ctl, &tmp, 0, 0, TB_CFG_SWITCH,
				      0, 1, 100);
		if (!res.err)
			return 0;

		msleep(50);
	} while (--retries);

	tb_err(tb, "failed to read root switch config space, giving up\n");
	return -ETIMEDOUT;
}