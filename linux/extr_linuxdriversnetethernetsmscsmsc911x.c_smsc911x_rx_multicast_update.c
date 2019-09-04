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
struct smsc911x_data {unsigned int set_bits_mask; unsigned int clear_bits_mask; unsigned int hashhi; unsigned int hashlo; } ;

/* Variables and functions */
 int /*<<< orphan*/  HASHH ; 
 int /*<<< orphan*/  HASHL ; 
 int /*<<< orphan*/  MAC_CR ; 
 int /*<<< orphan*/  SMSC_ASSERT_MAC_LOCK (struct smsc911x_data*) ; 
 int /*<<< orphan*/  SMSC_TRACE (struct smsc911x_data*,int /*<<< orphan*/ ,char*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  hw ; 
 unsigned int smsc911x_mac_read (struct smsc911x_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc911x_mac_write (struct smsc911x_data*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void smsc911x_rx_multicast_update(struct smsc911x_data *pdata)
{
	/* Performs the multicast & mac_cr update.  This is called when
	 * safe on the current hardware, and with the mac_lock held */
	unsigned int mac_cr;

	SMSC_ASSERT_MAC_LOCK(pdata);

	mac_cr = smsc911x_mac_read(pdata, MAC_CR);
	mac_cr |= pdata->set_bits_mask;
	mac_cr &= ~(pdata->clear_bits_mask);
	smsc911x_mac_write(pdata, MAC_CR, mac_cr);
	smsc911x_mac_write(pdata, HASHH, pdata->hashhi);
	smsc911x_mac_write(pdata, HASHL, pdata->hashlo);
	SMSC_TRACE(pdata, hw, "maccr 0x%08X, HASHH 0x%08X, HASHL 0x%08X",
		   mac_cr, pdata->hashhi, pdata->hashlo);
}