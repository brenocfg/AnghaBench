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
typedef  int npy_uint32 ;
struct TYPE_4__ {int length; int* blocks; } ;
typedef  TYPE_1__ BigInt ;

/* Variables and functions */

__attribute__((used)) static void
BigInt_Copy(BigInt *dst, const BigInt *src)
{
    npy_uint32 length = src->length;
    npy_uint32 * dstp = dst->blocks;
    const npy_uint32 *srcp;
    for (srcp = src->blocks; srcp != src->blocks + length; ++dstp, ++srcp) {
        *dstp = *srcp;
    }
    dst->length = length;
}