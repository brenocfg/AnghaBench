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

__attribute__((used)) static unsigned
id_prefix_count(unsigned id)
{
#define TWO_BYTE       ((unsigned long long)(~0)<<7)
#define THREE_BYTE     ((unsigned long long)(~0)<<14)
#define FOUR_BYTE      ((unsigned long long)(~0)<<21)
#define FIVE_BYTE      ((unsigned long long)(~0)<<28)
    
    if (id & FIVE_BYTE)
        return 4;
    if (id & FOUR_BYTE)
        return 3;
    if (id & THREE_BYTE)
        return 2;
    if (id & TWO_BYTE)
        return 1;
    return 0;
}