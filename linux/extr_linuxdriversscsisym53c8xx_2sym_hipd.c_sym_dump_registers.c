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
typedef  int /*<<< orphan*/  u_short ;
typedef  int /*<<< orphan*/  u_char ;
struct sym_hcb {int dummy; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INB (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INW (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nc_dstat ; 
 int /*<<< orphan*/  nc_sist ; 
 struct sym_hcb* sym_get_hcb (struct Scsi_Host*) ; 
 int /*<<< orphan*/  sym_log_hard_error (struct Scsi_Host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sym_dump_registers(struct Scsi_Host *shost)
{
	struct sym_hcb *np = sym_get_hcb(shost);
	u_short sist;
	u_char dstat;

	sist = INW(np, nc_sist);
	dstat = INB(np, nc_dstat);
	sym_log_hard_error(shost, sist, dstat);
}