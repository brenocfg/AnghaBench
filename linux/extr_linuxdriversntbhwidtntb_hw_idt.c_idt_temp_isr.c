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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct idt_ntb_dev {TYPE_2__ ntb; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDT_NTINTSTS_TMPSENSOR ; 
 int /*<<< orphan*/  IDT_NT_NTINTSTS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  idt_nt_write (struct idt_ntb_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idt_read_temp (struct idt_ntb_dev*,unsigned char*,unsigned char*) ; 

__attribute__((used)) static void idt_temp_isr(struct idt_ntb_dev *ndev, u32 ntint_sts)
{
	unsigned char val, frac;

	/* Read the current temperature value */
	idt_read_temp(ndev, &val, &frac);

	/* Read the temperature alarm to clean the alarm status out */
	/*(void)idt_sw_read(ndev, IDT_SW_TMPALARM);*/

	/* Clean the corresponding interrupt bit */
	idt_nt_write(ndev, IDT_NT_NTINTSTS, IDT_NTINTSTS_TMPSENSOR);

	dev_dbg(&ndev->ntb.pdev->dev,
		"Temp sensor IRQ detected %#08x", ntint_sts);

	/* Print temperature value to log */
	dev_warn(&ndev->ntb.pdev->dev, "Temperature %hhu.%hhu", val, frac);
}