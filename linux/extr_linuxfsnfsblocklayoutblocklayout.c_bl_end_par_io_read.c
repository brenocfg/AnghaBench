#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  tk_work; } ;
struct TYPE_4__ {TYPE_1__ u; int /*<<< orphan*/  tk_status; } ;
struct nfs_pgio_header {TYPE_2__ task; int /*<<< orphan*/  pnfs_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bl_read_cleanup ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bl_end_par_io_read(void *data)
{
	struct nfs_pgio_header *hdr = data;

	hdr->task.tk_status = hdr->pnfs_error;
	INIT_WORK(&hdr->task.u.tk_work, bl_read_cleanup);
	schedule_work(&hdr->task.u.tk_work);
}