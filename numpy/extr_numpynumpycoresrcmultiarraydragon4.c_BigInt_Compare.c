#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ npy_int32 ;
struct TYPE_4__ {scalar_t__ length; scalar_t__* blocks; } ;
typedef  TYPE_1__ BigInt ;

/* Variables and functions */

__attribute__((used)) static npy_int32
BigInt_Compare(const BigInt *lhs, const BigInt *rhs)
{
    int i;

    /* A bigger length implies a bigger number. */
    npy_int32 lengthDiff = lhs->length - rhs->length;
    if (lengthDiff != 0) {
        return lengthDiff;
    }

    /* Compare blocks one by one from high to low. */
    for (i = lhs->length - 1; i >= 0; --i) {
        if (lhs->blocks[i] == rhs->blocks[i]) {
            continue;
        }
        else if (lhs->blocks[i] > rhs->blocks[i]) {
            return 1;
        }
        else {
            return -1;
        }
    }

    /* no blocks differed */
    return 0;
}