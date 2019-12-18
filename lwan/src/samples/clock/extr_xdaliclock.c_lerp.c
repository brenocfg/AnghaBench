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
typedef  int uint32_t ;
typedef  int POS ;

/* Variables and functions */

__attribute__((used)) static inline POS lerp(POS a, POS b, unsigned int anim)
{
    uint32_t part_a = a * (65536 - anim);
    uint32_t part_b = b * (anim + 1);

    return (POS)((part_a + part_b) / 65536);
}