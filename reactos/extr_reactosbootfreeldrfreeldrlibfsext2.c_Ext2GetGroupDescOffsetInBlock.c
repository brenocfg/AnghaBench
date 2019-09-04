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
typedef  int ULONG ;
typedef  int /*<<< orphan*/  EXT2_GROUP_DESC ;

/* Variables and functions */
 int Ext2GroupDescPerBlock ; 

ULONG Ext2GetGroupDescOffsetInBlock(ULONG Group)
{
    return ((Group * sizeof(EXT2_GROUP_DESC)) % Ext2GroupDescPerBlock);
}