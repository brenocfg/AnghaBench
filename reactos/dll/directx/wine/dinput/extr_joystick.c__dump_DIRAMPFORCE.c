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
struct TYPE_3__ {int /*<<< orphan*/  lEnd; int /*<<< orphan*/  lStart; } ;
typedef  TYPE_1__* LPCDIRAMPFORCE ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _dump_DIRAMPFORCE(LPCDIRAMPFORCE frc)
{
    TRACE("Ramp force has start %d, end %d\n",
          frc->lStart, frc->lEnd);
}