#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_2__ {int inodes_per_group; } ;

/* Variables and functions */
 int Ext2InodesPerBlock ; 
 TYPE_1__* Ext2SuperBlock ; 

ULONG Ext2GetInodeOffsetInBlock(ULONG Inode)
{
    return (((Inode - 1) % Ext2SuperBlock->inodes_per_group) % Ext2InodesPerBlock);
}