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
typedef  size_t u_int ;
struct seq_file {int dummy; } ;
struct scsi_target {int dummy; } ;
struct scsi_device {int dummy; } ;
struct ahd_tmode_tstate {int dummy; } ;
struct ahd_softc {TYPE_1__* platform_data; } ;
struct ahd_initiator_tinfo {int /*<<< orphan*/  curr; int /*<<< orphan*/  goal; int /*<<< orphan*/  user; } ;
struct TYPE_2__ {struct scsi_target** starget; } ;

/* Variables and functions */
 int AHD_NUM_LUNS ; 
 int /*<<< orphan*/  ahd_dump_device_state (struct seq_file*,struct scsi_device*) ; 
 struct ahd_initiator_tinfo* ahd_fetch_transinfo (struct ahd_softc*,char,size_t,size_t,struct ahd_tmode_tstate**) ; 
 int /*<<< orphan*/  ahd_format_transinfo (struct seq_file*,int /*<<< orphan*/ *) ; 
 struct scsi_device* scsi_device_lookup_by_target (struct scsi_target*,int) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,size_t) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void
ahd_dump_target_state(struct ahd_softc *ahd, struct seq_file *m,
		      u_int our_id, char channel, u_int target_id)
{
	struct  scsi_target *starget;
	struct	ahd_initiator_tinfo *tinfo;
	struct	ahd_tmode_tstate *tstate;
	int	lun;

	tinfo = ahd_fetch_transinfo(ahd, channel, our_id,
				    target_id, &tstate);
	seq_printf(m, "Target %d Negotiation Settings\n", target_id);
	seq_puts(m, "\tUser: ");
	ahd_format_transinfo(m, &tinfo->user);
	starget = ahd->platform_data->starget[target_id];
	if (starget == NULL)
		return;

	seq_puts(m, "\tGoal: ");
	ahd_format_transinfo(m, &tinfo->goal);
	seq_puts(m, "\tCurr: ");
	ahd_format_transinfo(m, &tinfo->curr);

	for (lun = 0; lun < AHD_NUM_LUNS; lun++) {
		struct scsi_device *dev;

		dev = scsi_device_lookup_by_target(starget, lun);

		if (dev == NULL)
			continue;

		ahd_dump_device_state(m, dev);
	}
}