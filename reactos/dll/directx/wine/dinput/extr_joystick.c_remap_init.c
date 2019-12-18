#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* props; } ;
struct TYPE_7__ {int /*<<< orphan*/  lSaturation; int /*<<< orphan*/  lDeadZone; int /*<<< orphan*/  lMax; int /*<<< orphan*/  lDevMax; int /*<<< orphan*/  lMin; int /*<<< orphan*/  lDevMin; } ;
struct TYPE_6__ {int /*<<< orphan*/  lSaturation; int /*<<< orphan*/  lDeadZone; int /*<<< orphan*/  lMax; int /*<<< orphan*/  lMin; } ;
typedef  TYPE_2__ ObjProps ;
typedef  TYPE_3__ JoystickGenericImpl ;

/* Variables and functions */

__attribute__((used)) static void remap_init(JoystickGenericImpl *This, int obj, ObjProps *remap_props)
{
    /* Configure as if nothing changed so the helper functions can only change
     * what they need, thus reducing code duplication. */
    remap_props->lDevMin = remap_props->lMin = This->props[obj].lMin;
    remap_props->lDevMax = remap_props->lMax = This->props[obj].lMax;

    remap_props->lDeadZone = This->props[obj].lDeadZone;
    remap_props->lSaturation = This->props[obj].lSaturation;
}