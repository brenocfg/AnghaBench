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
struct sdebug_dev_info {int dummy; } ;
struct scsi_cmnd {int dummy; } ;

/* Variables and functions */
 int SDEBUG_READCAP_ARR_SZ ; 
 int fill_from_dev_buffer (struct scsi_cmnd*,unsigned char*,int) ; 
 int get_sdebug_capacity () ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_unaligned_be16 (int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  put_unaligned_be32 (int,unsigned char*) ; 
 int sdebug_capacity ; 
 int /*<<< orphan*/  sdebug_sector_size ; 

__attribute__((used)) static int resp_readcap(struct scsi_cmnd *scp,
			struct sdebug_dev_info *devip)
{
	unsigned char arr[SDEBUG_READCAP_ARR_SZ];
	unsigned int capac;

	/* following just in case virtual_gb changed */
	sdebug_capacity = get_sdebug_capacity();
	memset(arr, 0, SDEBUG_READCAP_ARR_SZ);
	if (sdebug_capacity < 0xffffffff) {
		capac = (unsigned int)sdebug_capacity - 1;
		put_unaligned_be32(capac, arr + 0);
	} else
		put_unaligned_be32(0xffffffff, arr + 0);
	put_unaligned_be16(sdebug_sector_size, arr + 6);
	return fill_from_dev_buffer(scp, arr, SDEBUG_READCAP_ARR_SZ);
}