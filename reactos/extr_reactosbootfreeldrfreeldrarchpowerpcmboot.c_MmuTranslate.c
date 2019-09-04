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
typedef  int paddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  mmu_handle ; 
 scalar_t__ ofproxy ; 
 int /*<<< orphan*/  ofw_callmethod_ret (char*,int /*<<< orphan*/ ,int,int*,int) ; 

paddr_t MmuTranslate(paddr_t possibly_virtual)
{
    if (ofproxy)
    {
        /* Openfirmware takes liberties with boot-time memory.
         * if you're in a unitary kernel, it's not as difficult, but since
         * we rely on loading things into virtual space from here, we need
         * to detect the mappings so far.
         */
        int args[2];
        args[0] = possibly_virtual;
        args[1] = 1; /* Marker to tell we want a physical addr */
        return (paddr_t)ofw_callmethod_ret("translate", mmu_handle, 2, args, 3);
    }
    else
    {
        /* Other booters don't remap ram */
        return possibly_virtual;
    }
}