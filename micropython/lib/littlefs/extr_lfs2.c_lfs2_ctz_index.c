#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* cfg; } ;
typedef  TYPE_2__ lfs2_t ;
typedef  int lfs2_off_t ;
struct TYPE_4__ {int block_size; } ;

/* Variables and functions */
 int lfs2_popc (int) ; 

__attribute__((used)) static int lfs2_ctz_index(lfs2_t *lfs2, lfs2_off_t *off) {
    lfs2_off_t size = *off;
    lfs2_off_t b = lfs2->cfg->block_size - 2*4;
    lfs2_off_t i = size / b;
    if (i == 0) {
        return 0;
    }

    i = (size - 4*(lfs2_popc(i-1)+2)) / b;
    *off = size - b*i - 4*lfs2_popc(i);
    return i;
}