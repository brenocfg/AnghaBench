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
typedef  int int8_t ;

/* Variables and functions */
 int crot (int const,int) ; 

__attribute__((used)) static void rotate_90(const uint8_t *src, uint8_t *dest) {
    for (uint8_t i = 0, shift = 7; i < 8; ++i, --shift) {
        uint8_t selector = (1 << i);
        for (uint8_t j = 0; j < 8; ++j) {
            dest[i] |= crot(src[j] & selector, shift - (int8_t)j);
        }
    }
}