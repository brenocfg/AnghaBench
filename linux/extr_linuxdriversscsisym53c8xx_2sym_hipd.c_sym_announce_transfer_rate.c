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
struct TYPE_2__ {scalar_t__ period; scalar_t__ offset; scalar_t__ width; scalar_t__ iu; scalar_t__ dt; scalar_t__ qas; int check_nego; } ;
struct sym_tcb {TYPE_1__ tprint; struct scsi_target* starget; } ;
struct scsi_target {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  spi_display_xfer_agreement (struct scsi_target*) ; 
 scalar_t__ spi_dt (struct scsi_target*) ; 
 scalar_t__ spi_iu (struct scsi_target*) ; 
 scalar_t__ spi_offset (struct scsi_target*) ; 
 scalar_t__ spi_period (struct scsi_target*) ; 
 scalar_t__ spi_qas (struct scsi_target*) ; 
 scalar_t__ spi_width (struct scsi_target*) ; 

__attribute__((used)) static void sym_announce_transfer_rate(struct sym_tcb *tp)
{
	struct scsi_target *starget = tp->starget;

	if (tp->tprint.period != spi_period(starget) ||
	    tp->tprint.offset != spi_offset(starget) ||
	    tp->tprint.width != spi_width(starget) ||
	    tp->tprint.iu != spi_iu(starget) ||
	    tp->tprint.dt != spi_dt(starget) ||
	    tp->tprint.qas != spi_qas(starget) ||
	    !tp->tprint.check_nego) {
		tp->tprint.period = spi_period(starget);
		tp->tprint.offset = spi_offset(starget);
		tp->tprint.width = spi_width(starget);
		tp->tprint.iu = spi_iu(starget);
		tp->tprint.dt = spi_dt(starget);
		tp->tprint.qas = spi_qas(starget);
		tp->tprint.check_nego = 1;

		spi_display_xfer_agreement(starget);
	}
}