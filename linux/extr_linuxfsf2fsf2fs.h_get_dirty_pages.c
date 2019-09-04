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
struct TYPE_2__ {int /*<<< orphan*/  dirty_pages; } ;

/* Variables and functions */
 TYPE_1__* F2FS_I (struct inode*) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int get_dirty_pages(struct inode *inode)
{
	return atomic_read(&F2FS_I(inode)->dirty_pages);
}