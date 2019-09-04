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
struct bfad_s {TYPE_1__* im; } ;
struct bfad_im_port_s {int flags; int /*<<< orphan*/  bfad; } ;
struct TYPE_2__ {int /*<<< orphan*/  drv_workq; } ;

/* Variables and functions */
 int BFAD_PORT_DELETE ; 
 int /*<<< orphan*/  bfad_im_port_clean (struct bfad_im_port_s*) ; 
 int /*<<< orphan*/  bfad_im_scsi_host_free (int /*<<< orphan*/ ,struct bfad_im_port_s*) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bfad_im_port_s*) ; 

void
bfad_scsi_host_free(struct bfad_s *bfad, struct bfad_im_port_s *im_port)
{
	if (!(im_port->flags & BFAD_PORT_DELETE))
		flush_workqueue(bfad->im->drv_workq);
	bfad_im_scsi_host_free(im_port->bfad, im_port);
	bfad_im_port_clean(im_port);
	kfree(im_port);
}