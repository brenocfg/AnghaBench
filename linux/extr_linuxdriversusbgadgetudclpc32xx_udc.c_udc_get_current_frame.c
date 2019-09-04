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
typedef  int u16 ;
struct lpc32xx_udc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RD_FRAME ; 
 int /*<<< orphan*/  DAT_RD_FRAME ; 
 scalar_t__ udc_protocol_cmd_r (struct lpc32xx_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udc_protocol_cmd_w (struct lpc32xx_udc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 udc_get_current_frame(struct lpc32xx_udc *udc)
{
	u16 flo, fhi;

	udc_protocol_cmd_w(udc, CMD_RD_FRAME);
	flo = (u16) udc_protocol_cmd_r(udc, DAT_RD_FRAME);
	fhi = (u16) udc_protocol_cmd_r(udc, DAT_RD_FRAME);

	return (fhi << 8) | flo;
}