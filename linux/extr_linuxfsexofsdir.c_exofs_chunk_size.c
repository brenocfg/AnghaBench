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
struct inode {TYPE_1__* i_sb; } ;
struct TYPE_2__ {int s_blocksize; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned exofs_chunk_size(struct inode *inode)
{
	return inode->i_sb->s_blocksize;
}