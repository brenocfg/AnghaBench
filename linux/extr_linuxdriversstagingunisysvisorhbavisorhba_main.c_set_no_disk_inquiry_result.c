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

/* Variables and functions */
 unsigned char DEV_DISK_CAPABLE_NOT_PRESENT ; 
 unsigned char DEV_HISUPPORT ; 
 unsigned char DEV_NOT_CAPABLE ; 
 int EINVAL ; 
 size_t NO_DISK_INQUIRY_RESULT_LEN ; 
 unsigned char SCSI_SPC2_VER ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  strncpy (unsigned char*,char*,size_t) ; 

__attribute__((used)) static int set_no_disk_inquiry_result(unsigned char *buf, size_t len,
				      bool is_lun0)
{
	if (len < NO_DISK_INQUIRY_RESULT_LEN)
		return -EINVAL;
	memset(buf, 0, NO_DISK_INQUIRY_RESULT_LEN);
	buf[2] = SCSI_SPC2_VER;
	if (is_lun0) {
		buf[0] = DEV_DISK_CAPABLE_NOT_PRESENT;
		buf[3] = DEV_HISUPPORT;
	} else {
		buf[0] = DEV_NOT_CAPABLE;
	}
	buf[4] = NO_DISK_INQUIRY_RESULT_LEN - 5;
	strncpy(buf + 8, "DELLPSEUDO DEVICE .", NO_DISK_INQUIRY_RESULT_LEN - 8);
	return 0;
}