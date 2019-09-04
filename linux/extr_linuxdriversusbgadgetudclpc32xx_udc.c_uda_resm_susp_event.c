#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct lpc32xx_udc {int suspended; TYPE_1__* board; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* susp_chgb ) (scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

__attribute__((used)) static void uda_resm_susp_event(struct lpc32xx_udc *udc, u32 conn)
{
	/* Just notify of a Suspend/resume change event (optional) */
	if (udc->board->susp_chgb != NULL)
		udc->board->susp_chgb(conn);

	if (conn)
		udc->suspended = 0;
	else
		udc->suspended = 1;
}