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
typedef  int u32 ;
struct platform_device {int dummy; } ;
struct dsi_data {int errors; int /*<<< orphan*/  errors_lock; } ;

/* Variables and functions */
 int DSI_CIO_IRQ_ERROR_MASK ; 
 int DSI_IRQ_ERROR_MASK ; 
 int DSI_VC_IRQ_ERROR_MASK ; 
 int /*<<< orphan*/  DSSERR (char*,int,...) ; 
 scalar_t__ debug_irq ; 
 struct dsi_data* dsi_get_dsidrv_data (struct platform_device*) ; 
 int /*<<< orphan*/  print_irq_status (int) ; 
 int /*<<< orphan*/  print_irq_status_cio (int) ; 
 int /*<<< orphan*/  print_irq_status_vc (int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dsi_handle_irq_errors(struct platform_device *dsidev, u32 irqstatus,
		u32 *vcstatus, u32 ciostatus)
{
	struct dsi_data *dsi = dsi_get_dsidrv_data(dsidev);
	int i;

	if (irqstatus & DSI_IRQ_ERROR_MASK) {
		DSSERR("DSI error, irqstatus %x\n", irqstatus);
		print_irq_status(irqstatus);
		spin_lock(&dsi->errors_lock);
		dsi->errors |= irqstatus & DSI_IRQ_ERROR_MASK;
		spin_unlock(&dsi->errors_lock);
	} else if (debug_irq) {
		print_irq_status(irqstatus);
	}

	for (i = 0; i < 4; ++i) {
		if (vcstatus[i] & DSI_VC_IRQ_ERROR_MASK) {
			DSSERR("DSI VC(%d) error, vc irqstatus %x\n",
				       i, vcstatus[i]);
			print_irq_status_vc(i, vcstatus[i]);
		} else if (debug_irq) {
			print_irq_status_vc(i, vcstatus[i]);
		}
	}

	if (ciostatus & DSI_CIO_IRQ_ERROR_MASK) {
		DSSERR("DSI CIO error, cio irqstatus %x\n", ciostatus);
		print_irq_status_cio(ciostatus);
	} else if (debug_irq) {
		print_irq_status_cio(ciostatus);
	}
}