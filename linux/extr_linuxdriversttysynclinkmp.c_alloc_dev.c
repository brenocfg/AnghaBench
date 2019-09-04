#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  irq; } ;
struct TYPE_6__ {int close_delay; int closing_wait; int /*<<< orphan*/ * ops; } ;
struct TYPE_5__ {int max_frame_size; int adapter_num; int port_num; int phys_lcr_base; int phys_sca_base; int phys_statctrl_base; int lcr_offset; int sca_offset; int statctrl_offset; int misc_ctrl_value; int init_error; int /*<<< orphan*/  status_timer; int /*<<< orphan*/  tx_timer; int /*<<< orphan*/  irq_flags; int /*<<< orphan*/  bus_type; void* phys_memory_base; int /*<<< orphan*/  irq_level; int /*<<< orphan*/  idle_mode; int /*<<< orphan*/  params; int /*<<< orphan*/  netlock; int /*<<< orphan*/  event_wait_q; int /*<<< orphan*/  status_event_wait_q; TYPE_2__ port; int /*<<< orphan*/  task; int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__ SLMP_INFO ;
typedef  int /*<<< orphan*/  MGSL_PARAMS ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HDLC_TXIDLE_FLAGS ; 
 int HZ ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  MGSL_BUS_TYPE_PCI ; 
 int /*<<< orphan*/  MGSL_MAGIC ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  bh_handler ; 
 int /*<<< orphan*/  default_params ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 void* pci_resource_start (struct pci_dev*,int) ; 
 int /*<<< orphan*/  port_ops ; 
 int /*<<< orphan*/  printk (char*,char*,int,int,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  status_timeout ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_port_init (TYPE_2__*) ; 
 int /*<<< orphan*/  tx_timeout ; 

__attribute__((used)) static SLMP_INFO *alloc_dev(int adapter_num, int port_num, struct pci_dev *pdev)
{
	SLMP_INFO *info;

	info = kzalloc(sizeof(SLMP_INFO),
		 GFP_KERNEL);

	if (!info) {
		printk("%s(%d) Error can't allocate device instance data for adapter %d, port %d\n",
			__FILE__,__LINE__, adapter_num, port_num);
	} else {
		tty_port_init(&info->port);
		info->port.ops = &port_ops;
		info->magic = MGSL_MAGIC;
		INIT_WORK(&info->task, bh_handler);
		info->max_frame_size = 4096;
		info->port.close_delay = 5*HZ/10;
		info->port.closing_wait = 30*HZ;
		init_waitqueue_head(&info->status_event_wait_q);
		init_waitqueue_head(&info->event_wait_q);
		spin_lock_init(&info->netlock);
		memcpy(&info->params,&default_params,sizeof(MGSL_PARAMS));
		info->idle_mode = HDLC_TXIDLE_FLAGS;
		info->adapter_num = adapter_num;
		info->port_num = port_num;

		/* Copy configuration info to device instance data */
		info->irq_level = pdev->irq;
		info->phys_lcr_base = pci_resource_start(pdev,0);
		info->phys_sca_base = pci_resource_start(pdev,2);
		info->phys_memory_base = pci_resource_start(pdev,3);
		info->phys_statctrl_base = pci_resource_start(pdev,4);

		/* Because veremap only works on page boundaries we must map
		 * a larger area than is actually implemented for the LCR
		 * memory range. We map a full page starting at the page boundary.
		 */
		info->lcr_offset    = info->phys_lcr_base & (PAGE_SIZE-1);
		info->phys_lcr_base &= ~(PAGE_SIZE-1);

		info->sca_offset    = info->phys_sca_base & (PAGE_SIZE-1);
		info->phys_sca_base &= ~(PAGE_SIZE-1);

		info->statctrl_offset    = info->phys_statctrl_base & (PAGE_SIZE-1);
		info->phys_statctrl_base &= ~(PAGE_SIZE-1);

		info->bus_type = MGSL_BUS_TYPE_PCI;
		info->irq_flags = IRQF_SHARED;

		timer_setup(&info->tx_timer, tx_timeout, 0);
		timer_setup(&info->status_timer, status_timeout, 0);

		/* Store the PCI9050 misc control register value because a flaw
		 * in the PCI9050 prevents LCR registers from being read if
		 * BIOS assigns an LCR base address with bit 7 set.
		 *
		 * Only the misc control register is accessed for which only
		 * write access is needed, so set an initial value and change
		 * bits to the device instance data as we write the value
		 * to the actual misc control register.
		 */
		info->misc_ctrl_value = 0x087e4546;

		/* initial port state is unknown - if startup errors
		 * occur, init_error will be set to indicate the
		 * problem. Once the port is fully initialized,
		 * this value will be set to 0 to indicate the
		 * port is available.
		 */
		info->init_error = -1;
	}

	return info;
}