#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int rc; int /*<<< orphan*/  comp; } ;
struct TYPE_6__ {TYPE_1__ mbx; } ;
struct TYPE_7__ {TYPE_2__ u; } ;
struct TYPE_8__ {TYPE_3__ iocb_cmd; } ;
struct srb {TYPE_4__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qla2x00_async_mb_sp_done(void *s, int res)
{
	struct srb *sp = s;

	sp->u.iocb_cmd.u.mbx.rc = res;

	complete(&sp->u.iocb_cmd.u.mbx.comp);
	/* don't free sp here. Let the caller do the free */
}