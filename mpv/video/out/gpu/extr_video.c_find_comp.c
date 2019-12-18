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
struct ra_imgfmt_desc {int num_planes; int** components; } ;

/* Variables and functions */

__attribute__((used)) static int find_comp(struct ra_imgfmt_desc *desc, int component)
{
    int cur = 0;
    for (int n = 0; n < desc->num_planes; n++) {
        for (int i = 0; i < 4; i++) {
            if (desc->components[n][i]) {
                if (desc->components[n][i] == component)
                    return cur;
                cur++;
            }
        }
    }
    return -1;
}