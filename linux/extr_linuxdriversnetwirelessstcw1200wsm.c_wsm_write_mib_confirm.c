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
struct wsm_mib {scalar_t__ mib_id; char* buf; } ;
struct wsm_buf {int dummy; } ;
struct cw1200_common {int dummy; } ;

/* Variables and functions */
 scalar_t__ WSM_MIB_ID_OPERATIONAL_POWER_MODE ; 
 int /*<<< orphan*/  cw1200_enable_powersave (struct cw1200_common*,int) ; 
 int wsm_generic_confirm (struct cw1200_common*,struct wsm_mib*,struct wsm_buf*) ; 

__attribute__((used)) static int wsm_write_mib_confirm(struct cw1200_common *priv,
				struct wsm_mib *arg,
				struct wsm_buf *buf)
{
	int ret;

	ret = wsm_generic_confirm(priv, arg, buf);
	if (ret)
		return ret;

	if (arg->mib_id == WSM_MIB_ID_OPERATIONAL_POWER_MODE) {
		/* OperationalMode: update PM status. */
		const char *p = arg->buf;
		cw1200_enable_powersave(priv, (p[0] & 0x0F) ? true : false);
	}
	return 0;
}