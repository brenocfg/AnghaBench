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
struct TYPE_3__ {struct TYPE_3__ const* Parent; int /*<<< orphan*/  const* Class; } ;
typedef  TYPE_1__ const MSIPROGID ;
typedef  int /*<<< orphan*/  MSICLASS ;

/* Variables and functions */

__attribute__((used)) static const MSICLASS *get_progid_class( const MSIPROGID *progid )
{
    while (progid)
    {
        if (progid->Parent) progid = progid->Parent;
        if (progid->Class) return progid->Class;
        if (!progid->Parent || progid->Parent == progid) break;
    }
    return NULL;
}