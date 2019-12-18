#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_6__ {int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_blocks; int /*<<< orphan*/  st_mode; } ;
struct TYPE_9__ {int atts; TYPE_3__* Vcb; TYPE_1__ inode_item; } ;
typedef  TYPE_4__ fcb ;
struct TYPE_7__ {int /*<<< orphan*/  sector_size; } ;
struct TYPE_8__ {TYPE_2__ superblock; } ;

/* Variables and functions */
 int FILE_ATTRIBUTE_SPARSE_FILE ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sector_align (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline uint64_t fcb_alloc_size(fcb* fcb) {
    if (S_ISDIR(fcb->inode_item.st_mode))
        return 0;
    else if (fcb->atts & FILE_ATTRIBUTE_SPARSE_FILE)
        return fcb->inode_item.st_blocks;
    else
        return sector_align(fcb->inode_item.st_size, fcb->Vcb->superblock.sector_size);
}