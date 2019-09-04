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
typedef  int /*<<< orphan*/  u8 ;
struct rtsx_chip {int dummy; } ;

/* Variables and functions */
 int MS_MAX_RETRY_COUNT ; 
 int /*<<< orphan*/  NO_WAIT_INT ; 
 int /*<<< orphan*/  SET_RW_REG_ADRS ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int ms_write_bytes (struct rtsx_chip*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rtsx_clear_ms_error (struct rtsx_chip*) ; 

__attribute__((used)) static int ms_set_rw_reg_addr(struct rtsx_chip *chip, u8 read_start,
			      u8 read_cnt, u8 write_start, u8 write_cnt)
{
	int retval, i;
	u8 data[4];

	data[0] = read_start;
	data[1] = read_cnt;
	data[2] = write_start;
	data[3] = write_cnt;

	for (i = 0; i < MS_MAX_RETRY_COUNT; i++) {
		retval = ms_write_bytes(chip, SET_RW_REG_ADRS, 4,
					NO_WAIT_INT, data, 4);
		if (retval == STATUS_SUCCESS)
			return STATUS_SUCCESS;
		rtsx_clear_ms_error(chip);
	}

	return STATUS_FAIL;
}