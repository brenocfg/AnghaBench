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
struct snic_tgt {int dummy; } ;
struct scsi_device {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  scsi_target (struct scsi_device*) ; 
 scalar_t__ snic_tgt_chkready (struct snic_tgt*) ; 
 struct snic_tgt* starget_to_tgt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
snic_slave_alloc(struct scsi_device *sdev)
{
	struct snic_tgt *tgt = starget_to_tgt(scsi_target(sdev));

	if (!tgt || snic_tgt_chkready(tgt))
		return -ENXIO;

	return 0;
}