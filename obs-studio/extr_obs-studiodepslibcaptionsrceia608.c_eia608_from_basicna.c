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
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  eia608_is_basicna (int) ; 
 int eia608_parity (int) ; 

uint16_t eia608_from_basicna(uint16_t bna1, uint16_t bna2)
{
    if (!eia608_is_basicna(bna1) || !eia608_is_basicna(bna2)) {
        return 0;
    }

    return eia608_parity((0xFF00 & bna1) | ((0xFF00 & bna2) >> 8));
}