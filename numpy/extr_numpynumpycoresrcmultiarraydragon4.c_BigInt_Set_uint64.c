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
typedef  int npy_uint64 ;
struct TYPE_3__ {int* blocks; int length; } ;
typedef  TYPE_1__ BigInt ;

/* Variables and functions */
 int bitmask_u64 (int) ; 

__attribute__((used)) static void
BigInt_Set_uint64(BigInt *i, npy_uint64 val)
{
    if (val > bitmask_u64(32)) {
        i->blocks[0] = val & bitmask_u64(32);
        i->blocks[1] = (val >> 32) & bitmask_u64(32);
        i->length = 2;
    }
    else if (val != 0) {
        i->blocks[0] = val & bitmask_u64(32);
        i->length = 1;
    }
    else {
        i->length = 0;
    }
}