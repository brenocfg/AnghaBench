#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_3__* dlgw; } ;
struct TYPE_18__ {TYPE_4__ u; scalar_t__ unicode; } ;
typedef  TYPE_7__ pagesetup_data ;
typedef  scalar_t__ WORD ;
struct TYPE_12__ {scalar_t__ dmOrientation; } ;
struct TYPE_13__ {TYPE_1__ s1; } ;
struct TYPE_20__ {TYPE_2__ u1; } ;
struct TYPE_17__ {scalar_t__ dmOrientation; } ;
struct TYPE_16__ {TYPE_6__ s1; } ;
struct TYPE_19__ {TYPE_5__ u1; } ;
struct TYPE_14__ {int /*<<< orphan*/  hDevMode; } ;
typedef  TYPE_8__ DEVMODEW ;
typedef  TYPE_9__ DEVMODEA ;

/* Variables and functions */
 scalar_t__ DMORIENT_LANDSCAPE ; 
 scalar_t__ DMORIENT_PORTRAIT ; 
 TYPE_8__* GlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void pagesetup_set_orientation(pagesetup_data *data, WORD orient)
{
    DEVMODEW *dm = GlobalLock(data->u.dlgw->hDevMode);

    assert(orient == DMORIENT_PORTRAIT || orient == DMORIENT_LANDSCAPE);

    if(data->unicode)
        dm->u1.s1.dmOrientation = orient;
    else
    {
        DEVMODEA *dmA = (DEVMODEA *)dm;
        dmA->u1.s1.dmOrientation = orient;
    }
    GlobalUnlock(data->u.dlgw->hDevMode);
}