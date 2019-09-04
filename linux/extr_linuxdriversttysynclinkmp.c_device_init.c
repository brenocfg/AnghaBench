#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  port_array ;
struct TYPE_11__ {int irq_requested; int /*<<< orphan*/  port; int /*<<< orphan*/  irq_level; int /*<<< orphan*/  device_name; int /*<<< orphan*/  irq_flags; int /*<<< orphan*/  lcr_base; int /*<<< orphan*/  statctrl_base; int /*<<< orphan*/  sca_base; int /*<<< orphan*/  memory_base; int /*<<< orphan*/  lock; int /*<<< orphan*/  port_array; } ;
typedef  TYPE_1__ SLMP_INFO ;

/* Variables and functions */
 int ENOMEM ; 
 int SCA_MAX_PORTS ; 
 int /*<<< orphan*/  adapter_test (TYPE_1__*) ; 
 int add_device (TYPE_1__*) ; 
 TYPE_1__* alloc_dev (int,int,struct pci_dev*) ; 
 int /*<<< orphan*/  alloc_dma_bufs (TYPE_1__*) ; 
 int /*<<< orphan*/  claim_resources (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_1__**,int) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_resources (TYPE_1__*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synclinkmp_interrupt ; 
 int /*<<< orphan*/  tty_port_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int device_init(int adapter_num, struct pci_dev *pdev)
{
	SLMP_INFO *port_array[SCA_MAX_PORTS];
	int port, rc;

	/* allocate device instances for up to SCA_MAX_PORTS devices */
	for ( port = 0; port < SCA_MAX_PORTS; ++port ) {
		port_array[port] = alloc_dev(adapter_num,port,pdev);
		if( port_array[port] == NULL ) {
			for (--port; port >= 0; --port) {
				tty_port_destroy(&port_array[port]->port);
				kfree(port_array[port]);
			}
			return -ENOMEM;
		}
	}

	/* give copy of port_array to all ports and add to device list  */
	for ( port = 0; port < SCA_MAX_PORTS; ++port ) {
		memcpy(port_array[port]->port_array,port_array,sizeof(port_array));
		rc = add_device( port_array[port] );
		if (rc)
			goto err_add;
		spin_lock_init(&port_array[port]->lock);
	}

	/* Allocate and claim adapter resources */
	if ( !claim_resources(port_array[0]) ) {

		alloc_dma_bufs(port_array[0]);

		/* copy resource information from first port to others */
		for ( port = 1; port < SCA_MAX_PORTS; ++port ) {
			port_array[port]->lock  = port_array[0]->lock;
			port_array[port]->irq_level     = port_array[0]->irq_level;
			port_array[port]->memory_base   = port_array[0]->memory_base;
			port_array[port]->sca_base      = port_array[0]->sca_base;
			port_array[port]->statctrl_base = port_array[0]->statctrl_base;
			port_array[port]->lcr_base      = port_array[0]->lcr_base;
			alloc_dma_bufs(port_array[port]);
		}

		rc = request_irq(port_array[0]->irq_level,
					synclinkmp_interrupt,
					port_array[0]->irq_flags,
					port_array[0]->device_name,
					port_array[0]);
		if ( rc ) {
			printk( "%s(%d):%s Can't request interrupt, IRQ=%d\n",
				__FILE__,__LINE__,
				port_array[0]->device_name,
				port_array[0]->irq_level );
			goto err_irq;
		}
		port_array[0]->irq_requested = true;
		adapter_test(port_array[0]);
	}
	return 0;
err_irq:
	release_resources( port_array[0] );
err_add:
	for ( port = 0; port < SCA_MAX_PORTS; ++port ) {
		tty_port_destroy(&port_array[port]->port);
		kfree(port_array[port]);
	}
	return rc;
}