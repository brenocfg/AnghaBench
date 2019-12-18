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
struct sigmadsp_control {int num_bytes; int /*<<< orphan*/  addr; } ;
struct sigmadsp {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* safeload ) (struct sigmadsp*,int /*<<< orphan*/ ,void*,int) ;} ;

/* Variables and functions */
 int sigmadsp_write (struct sigmadsp*,int /*<<< orphan*/ ,void*,int) ; 
 int stub1 (struct sigmadsp*,int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static int sigmadsp_ctrl_write(struct sigmadsp *sigmadsp,
	struct sigmadsp_control *ctrl, void *data)
{
	/* safeload loads up to 20 bytes in a atomic operation */
	if (ctrl->num_bytes <= 20 && sigmadsp->ops && sigmadsp->ops->safeload)
		return sigmadsp->ops->safeload(sigmadsp, ctrl->addr, data,
			ctrl->num_bytes);
	else
		return sigmadsp_write(sigmadsp, ctrl->addr, data,
			ctrl->num_bytes);
}