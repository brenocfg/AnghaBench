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
struct tmiofb_par {scalar_t__ lcr; } ;
struct fb_info {struct tmiofb_par* par; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ LCR_BBISC ; 
 unsigned int tmio_ioread16 (scalar_t__) ; 
 int /*<<< orphan*/  tmio_iowrite16 (unsigned int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t tmiofb_irq(int irq, void *__info)
{
	struct fb_info *info = __info;
	struct tmiofb_par *par = info->par;
	unsigned int bbisc = tmio_ioread16(par->lcr + LCR_BBISC);


	tmio_iowrite16(bbisc, par->lcr + LCR_BBISC);

#ifdef CONFIG_FB_TMIO_ACCELL
	/*
	 * We were in polling mode and now we got correct irq.
	 * Switch back to IRQ-based sync of command FIFO
	 */
	if (unlikely(par->use_polling && irq != -1)) {
		printk(KERN_INFO "tmiofb: switching to waitq\n");
		par->use_polling = false;
	}

	if (bbisc & 1)
		wake_up(&par->wait_acc);
#endif

	return IRQ_HANDLED;
}