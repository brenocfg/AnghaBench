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
struct tb_nhi {scalar_t__ iobase; } ;
typedef  enum nhi_fw_mode { ____Placeholder_nhi_fw_mode } nhi_fw_mode ;

/* Variables and functions */
 scalar_t__ REG_OUTMAIL_CMD ; 
 int REG_OUTMAIL_CMD_OPMODE_MASK ; 
 int REG_OUTMAIL_CMD_OPMODE_SHIFT ; 
 int ioread32 (scalar_t__) ; 

enum nhi_fw_mode nhi_mailbox_mode(struct tb_nhi *nhi)
{
	u32 val;

	val = ioread32(nhi->iobase + REG_OUTMAIL_CMD);
	val &= REG_OUTMAIL_CMD_OPMODE_MASK;
	val >>= REG_OUTMAIL_CMD_OPMODE_SHIFT;

	return (enum nhi_fw_mode)val;
}