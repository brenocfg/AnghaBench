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

inline int BatHit( int bath, int batl, int virt ) {
    int mask = 0xfffe0000 & ~((batl & 0x3f) << 17);
    return (batl & 0x40) && ((virt & mask) == (bath & mask));
}