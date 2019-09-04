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
typedef  int uint32_t ;

/* Variables and functions */
 int SHIFT24 (int) ; 
 int /*<<< orphan*/  abort () ; 

__attribute__((used)) static void convert_plane(int type, void *data, int num_samples)
{
    switch (type) {
    case 0:
        break;
    case 1: /* fall through */
    case 2: {
        int bytes = type == 1 ? 3 : 4;
        for (int s = 0; s < num_samples; s++) {
            uint32_t val = *((uint32_t *)data + s);
            uint8_t *ptr = (uint8_t *)data + s * bytes;
            ptr[0] = val >> SHIFT24(0);
            ptr[1] = val >> SHIFT24(1);
            ptr[2] = val >> SHIFT24(2);
            if (type == 2)
                ptr[3] = 0;
        }
        break;
    }
    default:
        abort();
    }
}