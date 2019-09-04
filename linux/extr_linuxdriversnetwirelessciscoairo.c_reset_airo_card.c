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
struct net_device {int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  name; struct airo_info* ml_priv; } ;
struct airo_info {int /*<<< orphan*/ * fids; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIRO_DEF_MTU ; 
 int /*<<< orphan*/  FLAG_MPI ; 
 int MAX_FIDS ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  airo_print_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  airo_print_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_interrupts (struct airo_info*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 scalar_t__ reset_card (struct net_device*,int) ; 
 scalar_t__ setup_card (struct airo_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transmit_allocate (struct airo_info*,int /*<<< orphan*/ ,int) ; 

int reset_airo_card( struct net_device *dev )
{
	int i;
	struct airo_info *ai = dev->ml_priv;

	if (reset_card (dev, 1))
		return -1;

	if ( setup_card(ai, dev->dev_addr, 1 ) != SUCCESS ) {
		airo_print_err(dev->name, "MAC could not be enabled");
		return -1;
	}
	airo_print_info(dev->name, "MAC enabled %pM", dev->dev_addr);
	/* Allocate the transmit buffers if needed */
	if (!test_bit(FLAG_MPI,&ai->flags))
		for( i = 0; i < MAX_FIDS; i++ )
			ai->fids[i] = transmit_allocate (ai,AIRO_DEF_MTU,i>=MAX_FIDS/2);

	enable_interrupts( ai );
	netif_wake_queue(dev);
	return 0;
}