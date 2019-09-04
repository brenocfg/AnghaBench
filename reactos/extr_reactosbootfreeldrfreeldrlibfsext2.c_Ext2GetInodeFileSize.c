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
typedef  int ULONGLONG ;
struct TYPE_3__ {int mode; scalar_t__ dir_acl; scalar_t__ size; } ;
typedef  TYPE_1__* PEXT2_INODE ;

/* Variables and functions */
 int EXT2_S_IFDIR ; 
 int EXT2_S_IFMT ; 

ULONGLONG Ext2GetInodeFileSize(PEXT2_INODE Inode)
{
    if ((Inode->mode & EXT2_S_IFMT) == EXT2_S_IFDIR)
    {
        return (ULONGLONG)(Inode->size);
    }
    else
    {
        return ((ULONGLONG)(Inode->size) | ((ULONGLONG)(Inode->dir_acl) << 32));
    }
}