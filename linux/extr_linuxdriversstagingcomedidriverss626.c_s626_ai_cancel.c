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
struct s626_private {scalar_t__ ai_cmd_running; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {scalar_t__ mmio; struct s626_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  S626_MC1_ERPS1 ; 
 scalar_t__ S626_P_IER ; 
 int /*<<< orphan*/  S626_P_MC1 ; 
 int /*<<< orphan*/  s626_mc_disable (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int s626_ai_cancel(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct s626_private *devpriv = dev->private;

	/* Stop RPS program in case it is currently running */
	s626_mc_disable(dev, S626_MC1_ERPS1, S626_P_MC1);

	/* disable master interrupt */
	writel(0, dev->mmio + S626_P_IER);

	devpriv->ai_cmd_running = 0;

	return 0;
}