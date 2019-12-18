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
struct TYPE_2__ {int i_advise; } ;

/* Variables and functions */
 TYPE_1__* F2FS_I (struct inode*) ; 

__attribute__((used)) static inline int is_file(struct inode *inode, int type)
{
	return F2FS_I(inode)->i_advise & type;
}