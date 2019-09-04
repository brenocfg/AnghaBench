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
struct TYPE_2__ {scalar_t__ i_ino; } ;
struct exofs_i_info {TYPE_1__ vfs_inode; } ;
typedef  scalar_t__ osd_id ;

/* Variables and functions */
 scalar_t__ EXOFS_OBJ_OFF ; 

__attribute__((used)) static inline osd_id exofs_oi_objno(struct exofs_i_info *oi)
{
	return oi->vfs_inode.i_ino + EXOFS_OBJ_OFF;
}