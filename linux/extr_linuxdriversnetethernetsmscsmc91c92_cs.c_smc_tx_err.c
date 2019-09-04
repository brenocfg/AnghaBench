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
struct smc_private {int duplex; int /*<<< orphan*/  packets_waiting; int /*<<< orphan*/  tx_err; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_aborted_errors; int /*<<< orphan*/  tx_window_errors; int /*<<< orphan*/  tx_carrier_errors; int /*<<< orphan*/  tx_errors; } ;
struct net_device {unsigned int base_addr; TYPE_1__ stats; } ;

/* Variables and functions */
 scalar_t__ DATA_1 ; 
 scalar_t__ FIFO_PORTS ; 
 int MC_FREEPKT ; 
 scalar_t__ MMU_CMD ; 
 scalar_t__ PNR_ARR ; 
 scalar_t__ POINTER ; 
 int PTR_AUTOINC ; 
 int PTR_READ ; 
 int /*<<< orphan*/  SMC_SELECT_BANK (int) ; 
 scalar_t__ TCR ; 
 int TCR_ENABLE ; 
 int TS_16COL ; 
 int TS_LATCOL ; 
 int TS_LOSTCAR ; 
 int TS_SUCCESS ; 
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  netdev_notice (struct net_device*,char*) ; 
 struct smc_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 

__attribute__((used)) static void smc_tx_err(struct net_device * dev)
{
    struct smc_private *smc = netdev_priv(dev);
    unsigned int ioaddr = dev->base_addr;
    int saved_packet = inw(ioaddr + PNR_ARR) & 0xff;
    int packet_no = inw(ioaddr + FIFO_PORTS) & 0x7f;
    int tx_status;

    /* select this as the packet to read from */
    outw(packet_no, ioaddr + PNR_ARR);

    /* read the first word from this packet */
    outw(PTR_AUTOINC | PTR_READ | 0, ioaddr + POINTER);

    tx_status = inw(ioaddr + DATA_1);

    dev->stats.tx_errors++;
    if (tx_status & TS_LOSTCAR) dev->stats.tx_carrier_errors++;
    if (tx_status & TS_LATCOL)  dev->stats.tx_window_errors++;
    if (tx_status & TS_16COL) {
	dev->stats.tx_aborted_errors++;
	smc->tx_err++;
    }

    if (tx_status & TS_SUCCESS) {
	netdev_notice(dev, "Successful packet caused error interrupt?\n");
    }
    /* re-enable transmit */
    SMC_SELECT_BANK(0);
    outw(inw(ioaddr + TCR) | TCR_ENABLE | smc->duplex, ioaddr + TCR);
    SMC_SELECT_BANK(2);

    outw(MC_FREEPKT, ioaddr + MMU_CMD); 	/* Free the packet memory. */

    /* one less packet waiting for me */
    smc->packets_waiting--;

    outw(saved_packet, ioaddr + PNR_ARR);
}