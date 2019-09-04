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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct scsi_cmnd {int dummy; } ;
struct ms_info {int dummy; } ;
struct rtsx_chip {struct ms_info ms_card; } ;

/* Variables and functions */
 scalar_t__ CHK_MSPRO (struct ms_info*) ; 
 int ms_rw_multi_sector (struct scsi_cmnd*,struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mspro_rw_multi_sector (struct scsi_cmnd*,struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ms_rw(struct scsi_cmnd *srb, struct rtsx_chip *chip,
	  u32 start_sector, u16 sector_cnt)
{
	struct ms_info *ms_card = &chip->ms_card;
	int retval;

	if (CHK_MSPRO(ms_card))
		retval = mspro_rw_multi_sector(srb, chip, start_sector,
					       sector_cnt);
	else
		retval = ms_rw_multi_sector(srb, chip, start_sector,
					    sector_cnt);

	return retval;
}