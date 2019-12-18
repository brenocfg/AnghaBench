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
typedef  scalar_t__ npy_uint32 ;
struct TYPE_3__ {int length; scalar_t__* blocks; } ;
typedef  TYPE_1__ BigInt ;

/* Variables and functions */

__attribute__((used)) static void
BigInt_Set_uint32(BigInt *i, npy_uint32 val)
{
    if (val != 0) {
        i->blocks[0] = val;
        i->length = 1;
    }
    else {
        i->length = 0;
    }
}