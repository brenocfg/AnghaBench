#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct videomode {int /*<<< orphan*/  flags; int /*<<< orphan*/  vsync_len; int /*<<< orphan*/  vback_porch; int /*<<< orphan*/  vfront_porch; int /*<<< orphan*/  vactive; int /*<<< orphan*/  hsync_len; int /*<<< orphan*/  hback_porch; int /*<<< orphan*/  hfront_porch; int /*<<< orphan*/  hactive; int /*<<< orphan*/  pixelclock; } ;
struct TYPE_18__ {int /*<<< orphan*/  typ; } ;
struct TYPE_17__ {int /*<<< orphan*/  typ; } ;
struct TYPE_16__ {int /*<<< orphan*/  typ; } ;
struct TYPE_15__ {int /*<<< orphan*/  typ; } ;
struct TYPE_14__ {int /*<<< orphan*/  typ; } ;
struct TYPE_13__ {int /*<<< orphan*/  typ; } ;
struct TYPE_12__ {int /*<<< orphan*/  typ; } ;
struct TYPE_11__ {int /*<<< orphan*/  typ; } ;
struct TYPE_10__ {int /*<<< orphan*/  typ; } ;
struct display_timing {int /*<<< orphan*/  flags; TYPE_9__ vsync_len; TYPE_8__ vback_porch; TYPE_7__ vfront_porch; TYPE_6__ vactive; TYPE_5__ hsync_len; TYPE_4__ hback_porch; TYPE_3__ hfront_porch; TYPE_2__ hactive; TYPE_1__ pixelclock; } ;

/* Variables and functions */

void videomode_from_timing(const struct display_timing *dt,
			  struct videomode *vm)
{
	vm->pixelclock = dt->pixelclock.typ;
	vm->hactive = dt->hactive.typ;
	vm->hfront_porch = dt->hfront_porch.typ;
	vm->hback_porch = dt->hback_porch.typ;
	vm->hsync_len = dt->hsync_len.typ;

	vm->vactive = dt->vactive.typ;
	vm->vfront_porch = dt->vfront_porch.typ;
	vm->vback_porch = dt->vback_porch.typ;
	vm->vsync_len = dt->vsync_len.typ;

	vm->flags = dt->flags;
}