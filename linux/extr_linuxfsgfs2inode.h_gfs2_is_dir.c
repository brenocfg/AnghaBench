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
struct TYPE_2__ {int /*<<< orphan*/  i_mode; } ;
struct gfs2_inode {TYPE_1__ i_inode; } ;

/* Variables and functions */
 int S_ISDIR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int gfs2_is_dir(const struct gfs2_inode *ip)
{
	return S_ISDIR(ip->i_inode.i_mode);
}