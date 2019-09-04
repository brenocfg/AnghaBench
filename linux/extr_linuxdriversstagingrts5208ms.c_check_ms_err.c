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
typedef  int u8 ;
struct rtsx_chip {int dummy; } ;

/* Variables and functions */
 int MS_INT_CMDNK ; 
 int MS_INT_ERR ; 
 int /*<<< orphan*/  MS_TRANSFER ; 
 int MS_TRANSFER_ERR ; 
 int /*<<< orphan*/  MS_TRANS_CFG ; 
 int STATUS_SUCCESS ; 
 int rtsx_read_register (struct rtsx_chip*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int check_ms_err(struct rtsx_chip *chip)
{
	int retval;
	u8 val;

	retval = rtsx_read_register(chip, MS_TRANSFER, &val);
	if (retval != STATUS_SUCCESS)
		return 1;
	if (val & MS_TRANSFER_ERR)
		return 1;

	retval = rtsx_read_register(chip, MS_TRANS_CFG, &val);
	if (retval != STATUS_SUCCESS)
		return 1;

	if (val & (MS_INT_ERR | MS_INT_CMDNK))
		return 1;

	return 0;
}