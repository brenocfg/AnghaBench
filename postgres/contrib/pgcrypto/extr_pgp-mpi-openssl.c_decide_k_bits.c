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

/* Variables and functions */

__attribute__((used)) static int
decide_k_bits(int p_bits)
{
	if (p_bits <= 5120)
		return p_bits / 10 + 160;
	else
		return (p_bits / 8 + 200) * 3 / 2;
}