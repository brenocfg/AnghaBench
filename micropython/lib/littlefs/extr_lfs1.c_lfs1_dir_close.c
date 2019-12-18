#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* dirs; } ;
typedef  TYPE_1__ lfs1_t ;
struct TYPE_6__ {struct TYPE_6__* next; } ;
typedef  TYPE_2__ lfs1_dir_t ;

/* Variables and functions */

int lfs1_dir_close(lfs1_t *lfs1, lfs1_dir_t *dir) {
    // remove from list of directories
    for (lfs1_dir_t **p = &lfs1->dirs; *p; p = &(*p)->next) {
        if (*p == dir) {
            *p = dir->next;
            break;
        }
    }

    return 0;
}