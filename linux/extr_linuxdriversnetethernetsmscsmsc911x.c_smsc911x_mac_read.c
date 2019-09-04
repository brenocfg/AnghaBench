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
struct smsc911x_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BYTE_TEST ; 
 int /*<<< orphan*/  MAC_CSR_CMD ; 
 unsigned int MAC_CSR_CMD_CSR_BUSY_ ; 
 unsigned int MAC_CSR_CMD_R_NOT_W_ ; 
 int /*<<< orphan*/  MAC_CSR_DATA ; 
 int /*<<< orphan*/  SMSC_ASSERT_MAC_LOCK (struct smsc911x_data*) ; 
 int /*<<< orphan*/  SMSC_WARN (struct smsc911x_data*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hw ; 
 scalar_t__ likely (int) ; 
 scalar_t__ smsc911x_mac_complete (struct smsc911x_data*) ; 
 int smsc911x_reg_read (struct smsc911x_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc911x_reg_write (struct smsc911x_data*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ unlikely (unsigned int) ; 

__attribute__((used)) static u32 smsc911x_mac_read(struct smsc911x_data *pdata, unsigned int offset)
{
	unsigned int temp;

	SMSC_ASSERT_MAC_LOCK(pdata);

	temp = smsc911x_reg_read(pdata, MAC_CSR_CMD);
	if (unlikely(temp & MAC_CSR_CMD_CSR_BUSY_)) {
		SMSC_WARN(pdata, hw, "MAC busy at entry");
		return 0xFFFFFFFF;
	}

	/* Send the MAC cmd */
	smsc911x_reg_write(pdata, MAC_CSR_CMD, ((offset & 0xFF) |
		MAC_CSR_CMD_CSR_BUSY_ | MAC_CSR_CMD_R_NOT_W_));

	/* Workaround for hardware read-after-write restriction */
	temp = smsc911x_reg_read(pdata, BYTE_TEST);

	/* Wait for the read to complete */
	if (likely(smsc911x_mac_complete(pdata) == 0))
		return smsc911x_reg_read(pdata, MAC_CSR_DATA);

	SMSC_WARN(pdata, hw, "MAC busy after read");
	return 0xFFFFFFFF;
}