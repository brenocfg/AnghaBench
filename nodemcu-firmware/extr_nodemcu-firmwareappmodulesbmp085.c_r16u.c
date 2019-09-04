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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int r8u (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint16_t r16u(uint32_t id, uint8_t reg) {
    uint8_t high = r8u(id, reg);
    uint8_t low  = r8u(id, reg + 1);
    return (high << 8) | low;
}