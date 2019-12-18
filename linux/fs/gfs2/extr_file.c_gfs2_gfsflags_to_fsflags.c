#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct TYPE_3__ {int gfsflag; int fsflag; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int GFS2_DIF_INHERIT_JDATA ; 
 int GFS2_DIF_JDATA ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 TYPE_1__* fsflag_gfs2flag ; 

__attribute__((used)) static inline u32 gfs2_gfsflags_to_fsflags(struct inode *inode, u32 gfsflags)
{
	int i;
	u32 fsflags = 0;

	if (S_ISDIR(inode->i_mode))
		gfsflags &= ~GFS2_DIF_JDATA;
	else
		gfsflags &= ~GFS2_DIF_INHERIT_JDATA;

	for (i = 0; i < ARRAY_SIZE(fsflag_gfs2flag); i++)
		if (gfsflags & fsflag_gfs2flag[i].gfsflag)
			fsflags |= fsflag_gfs2flag[i].fsflag;
	return fsflags;
}