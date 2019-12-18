#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ o_scenario_e ;
typedef  scalar_t__ BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAY (char*,...) ; 
 int displayLevel ; 
 scalar_t__ o_contiguous ; 

__attribute__((used)) static void locateBuffDiff(const void* buff1, const void* buff2, size_t size, o_scenario_e o_scenario)
{
    if (displayLevel >= 5) {
        size_t p=0;
        const BYTE* b1=(const BYTE*)buff1;
        const BYTE* b2=(const BYTE*)buff2;
        DISPLAY("locateBuffDiff: looking for error position \n");
        if (o_scenario != o_contiguous) {
            DISPLAY("mode %i: non-contiguous output (%u bytes), cannot search \n",
                    (int)o_scenario, (unsigned)size);
            return;
        }
        while (p < size && b1[p]==b2[p]) p++;
        if (p != size) {
            DISPLAY("Error at pos %i/%i : %02X != %02X \n", (int)p, (int)size, b1[p], b2[p]);
        }
    }
}