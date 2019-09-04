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
typedef  int /*<<< orphan*/  u16 ;
struct cw1200_common {int hw_type; } ;

/* Variables and functions */
#define  HIF_8601_SILICON 130 
#define  HIF_8601_VERSATILE 129 
#define  HIF_9000_SILICON_VERSATILE 128 
 int /*<<< orphan*/  ST90TDS_CONFIG_REG_ID ; 
 int cw1200_reg_write_16 (struct cw1200_common*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cw1200_reg_write_32 (struct cw1200_common*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_reg_write(struct cw1200_common *priv, u32 val)
{
	switch (priv->hw_type) {
	case HIF_9000_SILICON_VERSATILE:
		return cw1200_reg_write_16(priv,
					   ST90TDS_CONFIG_REG_ID,
					   (u16)val);
	case HIF_8601_VERSATILE:
	case HIF_8601_SILICON:
	default:
		return cw1200_reg_write_32(priv, ST90TDS_CONFIG_REG_ID, val);
	}
	return 0;
}