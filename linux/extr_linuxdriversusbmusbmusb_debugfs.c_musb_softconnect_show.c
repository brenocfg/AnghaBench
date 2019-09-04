#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct seq_file {struct musb* private; } ;
struct musb {int /*<<< orphan*/  controller; int /*<<< orphan*/  mregs; TYPE_2__* xceiv; } ;
struct TYPE_4__ {TYPE_1__* otg; } ;
struct TYPE_3__ {int state; } ;

/* Variables and functions */
 int /*<<< orphan*/  MUSB_DEVCTL ; 
 int MUSB_DEVCTL_SESSION ; 
#define  OTG_STATE_A_HOST 129 
#define  OTG_STATE_A_WAIT_BCON 128 
 int musb_readb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 

__attribute__((used)) static int musb_softconnect_show(struct seq_file *s, void *unused)
{
	struct musb	*musb = s->private;
	u8		reg;
	int		connect;

	switch (musb->xceiv->otg->state) {
	case OTG_STATE_A_HOST:
	case OTG_STATE_A_WAIT_BCON:
		pm_runtime_get_sync(musb->controller);

		reg = musb_readb(musb->mregs, MUSB_DEVCTL);
		connect = reg & MUSB_DEVCTL_SESSION ? 1 : 0;

		pm_runtime_mark_last_busy(musb->controller);
		pm_runtime_put_autosuspend(musb->controller);
		break;
	default:
		connect = -1;
	}

	seq_printf(s, "%d\n", connect);

	return 0;
}