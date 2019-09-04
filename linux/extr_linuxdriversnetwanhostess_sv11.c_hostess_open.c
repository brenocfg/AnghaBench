#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  rx_function; } ;
struct z8530_dev {TYPE_1__ chanA; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct z8530_dev* dev_to_sv (struct net_device*) ; 
 int dma ; 
 int hdlc_open (struct net_device*) ; 
 int /*<<< orphan*/  hostess_input ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  z8530_sync_close (struct net_device*,TYPE_1__*) ; 
 int /*<<< orphan*/  z8530_sync_dma_close (struct net_device*,TYPE_1__*) ; 
 int z8530_sync_dma_open (struct net_device*,TYPE_1__*) ; 
 int z8530_sync_open (struct net_device*,TYPE_1__*) ; 
 int /*<<< orphan*/  z8530_sync_txdma_close (struct net_device*,TYPE_1__*) ; 
 int z8530_sync_txdma_open (struct net_device*,TYPE_1__*) ; 

__attribute__((used)) static int hostess_open(struct net_device *d)
{
	struct z8530_dev *sv11 = dev_to_sv(d);
	int err = -1;

	/*
	 *	Link layer up
	 */
	switch (dma) {
		case 0:
			err = z8530_sync_open(d, &sv11->chanA);
			break;
		case 1:
			err = z8530_sync_dma_open(d, &sv11->chanA);
			break;
		case 2:
			err = z8530_sync_txdma_open(d, &sv11->chanA);
			break;
	}

	if (err)
		return err;

	err = hdlc_open(d);
	if (err) {
		switch (dma) {
			case 0:
				z8530_sync_close(d, &sv11->chanA);
				break;
			case 1:
				z8530_sync_dma_close(d, &sv11->chanA);
				break;
			case 2:
				z8530_sync_txdma_close(d, &sv11->chanA);
				break;
		}
		return err;
	}
	sv11->chanA.rx_function = hostess_input;

	/*
	 *	Go go go
	 */

	netif_start_queue(d);
	return 0;
}