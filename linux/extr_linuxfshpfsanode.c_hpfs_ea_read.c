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
struct buffer_head {int dummy; } ;
typedef  int secno ;
struct TYPE_2__ {scalar_t__ sb_chk; } ;

/* Variables and functions */
 int anode_lookup (struct super_block*,int,unsigned int) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ hpfs_chk_sectors (struct super_block*,int,int,char*) ; 
 char* hpfs_map_sector (struct super_block*,int,struct buffer_head**,unsigned int) ; 
 TYPE_1__* hpfs_sb (struct super_block*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,unsigned int) ; 

int hpfs_ea_read(struct super_block *s, secno a, int ano, unsigned pos,
	    unsigned len, char *buf)
{
	struct buffer_head *bh;
	char *data;
	secno sec;
	unsigned l;
	while (len) {
		if (ano) {
			if ((sec = anode_lookup(s, a, pos >> 9)) == -1)
				return -1;
		} else sec = a + (pos >> 9);
		if (hpfs_sb(s)->sb_chk) if (hpfs_chk_sectors(s, sec, 1, "ea #1")) return -1;
		if (!(data = hpfs_map_sector(s, sec, &bh, (len - 1) >> 9)))
			return -1;
		l = 0x200 - (pos & 0x1ff); if (l > len) l = len;
		memcpy(buf, data + (pos & 0x1ff), l);
		brelse(bh);
		buf += l; pos += l; len -= l;
	}
	return 0;
}