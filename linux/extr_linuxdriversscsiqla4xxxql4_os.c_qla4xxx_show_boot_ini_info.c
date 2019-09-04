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
struct scsi_qla_host {char* name_string; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ENOSYS ; 
#define  ISCSI_BOOT_INI_INITIATOR_NAME 128 
 int sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t qla4xxx_show_boot_ini_info(void *data, int type, char *buf)
{
	struct scsi_qla_host *ha = data;
	char *str = buf;
	int rc;

	switch (type) {
	case ISCSI_BOOT_INI_INITIATOR_NAME:
		rc = sprintf(str, "%s\n", ha->name_string);
		break;
	default:
		rc = -ENOSYS;
		break;
	}
	return rc;
}