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
struct cflayer {int /*<<< orphan*/  id; TYPE_1__* up; } ;
typedef  enum caif_ctrlcmd { ____Placeholder_caif_ctrlcmd } caif_ctrlcmd ;
struct TYPE_2__ {int /*<<< orphan*/  (* ctrlcmd ) (TYPE_1__*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cfusbl_ctrlcmd(struct cflayer *layr, enum caif_ctrlcmd ctrl,
			   int phyid)
{
	if (layr->up && layr->up->ctrlcmd)
		layr->up->ctrlcmd(layr->up, ctrl, layr->id);
}