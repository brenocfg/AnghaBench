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
struct csio_lnode {int dummy; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  csio_fchost_attr_init (struct csio_lnode*) ; 
 struct Scsi_Host* csio_ln_to_shost (struct csio_lnode*) ; 
 int /*<<< orphan*/  scsi_scan_host (struct Scsi_Host*) ; 

__attribute__((used)) static void
csio_lnode_init_post(struct csio_lnode *ln)
{
	struct Scsi_Host  *shost = csio_ln_to_shost(ln);

	csio_fchost_attr_init(ln);

	scsi_scan_host(shost);
}