#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dwFlags; int /*<<< orphan*/  tszName; int /*<<< orphan*/  dwType; int /*<<< orphan*/  dwOfs; int /*<<< orphan*/  guidType; } ;
typedef  TYPE_1__ DIDEVICEOBJECTINSTANCEA ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _dump_dinput_GUID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ *) ; 

void _dump_OBJECTINSTANCEA(const DIDEVICEOBJECTINSTANCEA *ddoi) {
    TRACE("    - enumerating : %s ('%s') - %2d - 0x%08x - %s - 0x%x\n",
        debugstr_guid(&ddoi->guidType), _dump_dinput_GUID(&ddoi->guidType), ddoi->dwOfs, ddoi->dwType, ddoi->tszName, ddoi->dwFlags);
}