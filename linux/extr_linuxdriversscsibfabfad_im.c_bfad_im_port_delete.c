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
struct bfad_port_s {struct bfad_im_port_s* im_port; } ;
struct bfad_im_port_s {int /*<<< orphan*/  port_delete_work; } ;
struct TYPE_2__ {int /*<<< orphan*/  drv_workq; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
bfad_im_port_delete(struct bfad_s *bfad, struct bfad_port_s *port)
{
	struct bfad_im_port_s *im_port = port->im_port;

	queue_work(bfad->im->drv_workq,
				&im_port->port_delete_work);
}