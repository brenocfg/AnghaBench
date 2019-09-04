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
typedef  int u32 ;
struct musb {int /*<<< orphan*/  ctrl_base; TYPE_1__* controller; } ;
struct dsps_musb_wrapper {int rxep_shift; int /*<<< orphan*/  epintr_status; } ;
struct dsps_glue {struct dsps_musb_wrapper* wrp; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 struct dsps_glue* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  musb_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dsps_musb_clear_ep_rxintr(struct musb *musb, int epnum)
{
	u32 epintr;
	struct dsps_glue *glue = dev_get_drvdata(musb->controller->parent);
	const struct dsps_musb_wrapper *wrp = glue->wrp;

	/* musb->lock might already been held */
	epintr = (1 << epnum) << wrp->rxep_shift;
	musb_writel(musb->ctrl_base, wrp->epintr_status, epintr);
}