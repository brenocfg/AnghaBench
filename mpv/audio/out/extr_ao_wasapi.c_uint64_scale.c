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
typedef  int UINT64 ;

/* Variables and functions */

__attribute__((used)) static UINT64 uint64_scale(UINT64 x, UINT64 num, UINT64 den)
{
    return (x / den) * num
        + ((x % den) * (num / den))
        + ((x % den) * (num % den)) / den;
}