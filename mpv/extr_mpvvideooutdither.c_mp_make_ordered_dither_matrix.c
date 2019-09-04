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

void mp_make_ordered_dither_matrix(unsigned char *m, int size)
{
    m[0] = 0;
    for (int sz = 1; sz < size; sz *= 2) {
        int offset[] = {sz*size, sz, sz * (size+1), 0};
        for (int i = 0; i < 4; i++)
            for (int y = 0; y < sz * size; y += size)
                for (int x = 0; x < sz; x++)
                    m[x+y+offset[i]] = m[x+y] * 4 + (3-i) * 256/size/size;
    }
}