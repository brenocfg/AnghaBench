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
typedef  int /*<<< orphan*/  which_be ;
typedef  int /*<<< orphan*/  u32 ;
struct ar5523 {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  AR5523_CMD_FLAG_MAGIC ; 
 int /*<<< orphan*/  WDCMSG_TARGET_GET_STATUS ; 
 int ar5523_cmd_read (struct ar5523*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar5523_err (struct ar5523*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ar5523_get_status(struct ar5523 *ar, u32 which, void *odata,
			     int olen)
{
	int error;
	__be32 which_be;

	which_be = cpu_to_be32(which);
	error = ar5523_cmd_read(ar, WDCMSG_TARGET_GET_STATUS,
	    &which_be, sizeof(which_be), odata, olen, AR5523_CMD_FLAG_MAGIC);
	if (error != 0)
		ar5523_err(ar, "could not read EEPROM offset 0x%02x\n", which);
	return error;
}