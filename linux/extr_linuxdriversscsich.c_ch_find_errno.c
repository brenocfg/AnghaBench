#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct scsi_sense_hdr {scalar_t__ asc; scalar_t__ sense_key; scalar_t__ ascq; } ;
struct TYPE_2__ {int errno; scalar_t__ sense; scalar_t__ asc; scalar_t__ ascq; } ;

/* Variables and functions */
 int EIO ; 
 TYPE_1__* ch_err ; 
 scalar_t__ scsi_sense_valid (struct scsi_sense_hdr*) ; 

__attribute__((used)) static int ch_find_errno(struct scsi_sense_hdr *sshdr)
{
	int i,errno = 0;

	/* Check to see if additional sense information is available */
	if (scsi_sense_valid(sshdr) &&
	    sshdr->asc != 0) {
		for (i = 0; ch_err[i].errno != 0; i++) {
			if (ch_err[i].sense == sshdr->sense_key &&
			    ch_err[i].asc   == sshdr->asc &&
			    ch_err[i].ascq  == sshdr->ascq) {
				errno = -ch_err[i].errno;
				break;
			}
		}
	}
	if (errno == 0)
		errno = -EIO;
	return errno;
}