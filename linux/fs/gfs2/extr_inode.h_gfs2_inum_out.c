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
struct gfs2_inode {int /*<<< orphan*/  i_no_addr; int /*<<< orphan*/  i_no_formal_ino; } ;
struct TYPE_2__ {void* no_addr; void* no_formal_ino; } ;
struct gfs2_dirent {TYPE_1__ de_inum; } ;

/* Variables and functions */
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void gfs2_inum_out(const struct gfs2_inode *ip,
				 struct gfs2_dirent *dent)
{
	dent->de_inum.no_formal_ino = cpu_to_be64(ip->i_no_formal_ino);
	dent->de_inum.no_addr = cpu_to_be64(ip->i_no_addr);
}