#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__ const* Parent; TYPE_1__* Class; } ;
struct TYPE_4__ {int /*<<< orphan*/ * clsid; } ;
typedef  TYPE_2__ const MSIPROGID ;
typedef  int /*<<< orphan*/ * LPCWSTR ;

/* Variables and functions */

__attribute__((used)) static LPCWSTR get_clsid_of_progid( const MSIPROGID *progid )
{
    while (progid)
    {
        if (progid->Class)
            return progid->Class->clsid;
        if (progid->Parent == progid)
            break;
        progid = progid->Parent;
    }
    return NULL;
}