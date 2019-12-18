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
struct ext4_xattr_ref {TYPE_1__* fs; } ;
typedef  int /*<<< orphan*/  __s32 ;
struct TYPE_2__ {int /*<<< orphan*/  BlockSize; } ;

/* Variables and functions */

__attribute__((used)) static __s32 ext4_xattr_block_space(struct ext4_xattr_ref *xattr_ref)
{
	return xattr_ref->fs->BlockSize;
}