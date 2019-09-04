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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  av_bswap16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void swap_16(uint16_t *ptr, size_t size)
{
    for (size_t n = 0; n < size; n++)
        ptr[n] = av_bswap16(ptr[n]);
}