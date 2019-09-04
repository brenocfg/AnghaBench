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
struct scsi_sense_hdr {scalar_t__ sense_key; int asc; int ascq; } ;
struct scsi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALUA_FAILOVER_RETRIES ; 
 int ALUA_FAILOVER_TIMEOUT ; 
 int HZ ; 
 scalar_t__ NOT_READY ; 
 int SCSI_DH_IO ; 
 int SCSI_DH_OK ; 
 int SCSI_DH_RETRY ; 
 int scsi_test_unit_ready (struct scsi_device*,int,int /*<<< orphan*/ ,struct scsi_sense_hdr*) ; 

__attribute__((used)) static int alua_tur(struct scsi_device *sdev)
{
	struct scsi_sense_hdr sense_hdr;
	int retval;

	retval = scsi_test_unit_ready(sdev, ALUA_FAILOVER_TIMEOUT * HZ,
				      ALUA_FAILOVER_RETRIES, &sense_hdr);
	if (sense_hdr.sense_key == NOT_READY &&
	    sense_hdr.asc == 0x04 && sense_hdr.ascq == 0x0a)
		return SCSI_DH_RETRY;
	else if (retval)
		return SCSI_DH_IO;
	else
		return SCSI_DH_OK;
}