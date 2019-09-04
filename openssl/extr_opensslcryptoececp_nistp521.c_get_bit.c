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
typedef  int* felem_bytearray ;

/* Variables and functions */

__attribute__((used)) static char get_bit(const felem_bytearray in, int i)
{
    if (i < 0)
        return 0;
    return (in[i >> 3] >> (i & 7)) & 1;
}