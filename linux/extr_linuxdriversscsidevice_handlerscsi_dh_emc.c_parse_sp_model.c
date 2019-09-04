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
struct scsi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLARIION_NAME ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 char* emc_default_str ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  strncmp (unsigned char*,char*,int) ; 

__attribute__((used)) static char * parse_sp_model(struct scsi_device *sdev, unsigned char *buffer)
{
	unsigned char len = buffer[4] + 5;
	char *sp_model = NULL;
	unsigned char sp_len, serial_len;

	if (len < 160) {
		sdev_printk(KERN_WARNING, sdev,
			    "%s: Invalid information section length %d\n",
			    CLARIION_NAME, len);
		/* Check for old FC arrays */
		if (!strncmp(buffer + 8, "DGC", 3)) {
			/* Old FC array, not supporting extended information */
			sp_model = emc_default_str;
		}
		goto out;
	}

	/*
	 * Parse extended information for SP model number
	 */
	serial_len = buffer[160];
	if (serial_len == 0 || serial_len + 161 > len) {
		sdev_printk(KERN_WARNING, sdev,
			    "%s: Invalid array serial number length %d\n",
			    CLARIION_NAME, serial_len);
		goto out;
	}
	sp_len = buffer[99];
	if (sp_len == 0 || serial_len + sp_len + 161 > len) {
		sdev_printk(KERN_WARNING, sdev,
			    "%s: Invalid model number length %d\n",
			    CLARIION_NAME, sp_len);
		goto out;
	}
	sp_model = &buffer[serial_len + 161];
	/* Strip whitespace at the end */
	while (sp_len > 1 && sp_model[sp_len - 1] == ' ')
		sp_len--;

	sp_model[sp_len] = '\0';

out:
	return sp_model;
}