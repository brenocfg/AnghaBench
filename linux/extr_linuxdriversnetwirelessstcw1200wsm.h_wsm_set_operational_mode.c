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
typedef  int /*<<< orphan*/  val ;
typedef  int /*<<< orphan*/  u8 ;
struct wsm_operational_mode {scalar_t__ perform_ant_diversity; scalar_t__ disable_more_flag_usage; int /*<<< orphan*/  power_mode; } ;
struct cw1200_common {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  WSM_MIB_ID_OPERATIONAL_POWER_MODE ; 
 int wsm_write_mib (struct cw1200_common*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int wsm_set_operational_mode(struct cw1200_common *priv,
					const struct wsm_operational_mode *arg)
{
	u8 val = arg->power_mode;
	if (arg->disable_more_flag_usage)
		val |= BIT(4);
	if (arg->perform_ant_diversity)
		val |= BIT(5);
	return wsm_write_mib(priv, WSM_MIB_ID_OPERATIONAL_POWER_MODE, &val,
			     sizeof(val));
}