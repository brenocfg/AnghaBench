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
struct super_block {int dummy; } ;
typedef  int secno ;
struct TYPE_2__ {int sb_fs_size; int sb_chk; } ;

/* Variables and functions */
 scalar_t__ chk_if_allocated (struct super_block*,int,char*) ; 
 int /*<<< orphan*/  hpfs_error (struct super_block*,char*,char*,int) ; 
 TYPE_1__* hpfs_sb (struct super_block*) ; 

int hpfs_chk_sectors(struct super_block *s, secno start, int len, char *msg)
{
	if (start + len < start || start < 0x12 ||
	    start + len > hpfs_sb(s)->sb_fs_size) {
	    	hpfs_error(s, "sector(s) '%s' badly placed at %08x", msg, start);
		return 1;
	}
	if (hpfs_sb(s)->sb_chk>=2) {
		int i;
		for (i = 0; i < len; i++)
			if (chk_if_allocated(s, start + i, msg)) return 1;
	}
	return 0;
}