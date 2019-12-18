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
typedef  scalar_t__ uint8_t ;
typedef  int uint64_t ;

/* Variables and functions */

uint64_t nn_getll (const uint8_t *buf)
{
    return (((uint64_t) buf [0]) << 56) |
           (((uint64_t) buf [1]) << 48) |
           (((uint64_t) buf [2]) << 40) |
           (((uint64_t) buf [3]) << 32) |
           (((uint64_t) buf [4]) << 24) |
           (((uint64_t) buf [5]) << 16) |
           (((uint64_t) buf [6]) << 8) |
           (((uint64_t) buf [7] << 0));
}