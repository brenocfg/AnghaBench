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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int* felem ;

/* Variables and functions */

__attribute__((used)) static void bin28_to_felem(felem out, const u8 in[28])
{
    out[0] = *((const uint64_t *)(in)) & 0x00ffffffffffffff;
    out[1] = (*((const uint64_t *)(in + 7))) & 0x00ffffffffffffff;
    out[2] = (*((const uint64_t *)(in + 14))) & 0x00ffffffffffffff;
    out[3] = (*((const uint64_t *)(in+20))) >> 8;
}