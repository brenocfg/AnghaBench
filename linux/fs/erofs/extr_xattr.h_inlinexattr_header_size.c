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
typedef  int /*<<< orphan*/  u32 ;
struct inode {int dummy; } ;
struct erofs_xattr_ibody_header {int dummy; } ;
struct TYPE_2__ {int xattr_shared_count; } ;

/* Variables and functions */
 TYPE_1__* EROFS_I (struct inode*) ; 

__attribute__((used)) static inline unsigned int inlinexattr_header_size(struct inode *inode)
{
	return sizeof(struct erofs_xattr_ibody_header) +
		sizeof(u32) * EROFS_I(inode)->xattr_shared_count;
}