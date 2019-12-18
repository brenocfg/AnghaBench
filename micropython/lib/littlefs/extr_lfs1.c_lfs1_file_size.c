#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lfs1_t ;
typedef  int /*<<< orphan*/  lfs1_soff_t ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  size; int /*<<< orphan*/  pos; } ;
typedef  TYPE_1__ lfs1_file_t ;

/* Variables and functions */
 int LFS1_F_WRITING ; 
 int /*<<< orphan*/  lfs1_max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

lfs1_soff_t lfs1_file_size(lfs1_t *lfs1, lfs1_file_t *file) {
    (void)lfs1;
    if (file->flags & LFS1_F_WRITING) {
        return lfs1_max(file->pos, file->size);
    } else {
        return file->size;
    }
}