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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IREG_IRQ_NUMBER ; 
 int /*<<< orphan*/  IREG_IRQ_TYPE ; 
 int /*<<< orphan*/  IREG_LOGDEVICE ; 
 int IRQTYPE_EDGE ; 
 int LOBYTE (int /*<<< orphan*/ ) ; 
 scalar_t__ snd_msnd_write_cfg (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int snd_msnd_write_cfg_irq(int cfg, int num, u16 irq)
{
	if (snd_msnd_write_cfg(cfg, IREG_LOGDEVICE, num))
		return -EIO;
	if (snd_msnd_write_cfg(cfg, IREG_IRQ_NUMBER, LOBYTE(irq)))
		return -EIO;
	if (snd_msnd_write_cfg(cfg, IREG_IRQ_TYPE, IRQTYPE_EDGE))
		return -EIO;
	return 0;
}