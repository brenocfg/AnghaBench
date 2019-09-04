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
struct lpc32xx_udc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_CFG_DEV ; 
 int /*<<< orphan*/  CONF_DVICE ; 
 int /*<<< orphan*/  DAT_WR_BYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udc_protocol_cmd_data_w (struct lpc32xx_udc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void udc_set_device_configured(struct lpc32xx_udc *udc)
{
	udc_protocol_cmd_data_w(udc, CMD_CFG_DEV, DAT_WR_BYTE(CONF_DVICE));
}