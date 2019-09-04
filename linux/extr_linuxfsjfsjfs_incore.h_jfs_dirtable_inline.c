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
struct inode {int dummy; } ;
struct TYPE_2__ {scalar_t__ next_index; } ;

/* Variables and functions */
 TYPE_1__* JFS_IP (struct inode*) ; 
 scalar_t__ MAX_INLINE_DIRTABLE_ENTRY ; 

__attribute__((used)) static inline int jfs_dirtable_inline(struct inode *inode)
{
	return (JFS_IP(inode)->next_index <= (MAX_INLINE_DIRTABLE_ENTRY + 1));
}