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
struct TYPE_2__ {int sb_chk; int /*<<< orphan*/  sb_cp_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int hpfs_is_name_long (unsigned char*,unsigned int) ; 
 TYPE_1__* hpfs_sb (struct super_block*) ; 
 unsigned char* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned char locase (int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

unsigned char *hpfs_translate_name(struct super_block *s, unsigned char *from,
			  unsigned len, int lc, int lng)
{
	unsigned char *to;
	int i;
	if (hpfs_sb(s)->sb_chk >= 2) if (hpfs_is_name_long(from, len) != lng) {
		pr_err("Long name flag mismatch - name ");
		for (i = 0; i < len; i++)
			pr_cont("%c", from[i]);
		pr_cont(" misidentified as %s.\n", lng ? "short" : "long");
		pr_err("It's nothing serious. It could happen because of bug in OS/2.\nSet checks=normal to disable this message.\n");
	}
	if (!lc) return from;
	if (!(to = kmalloc(len, GFP_KERNEL))) {
		pr_err("can't allocate memory for name conversion buffer\n");
		return from;
	}
	for (i = 0; i < len; i++) to[i] = locase(hpfs_sb(s)->sb_cp_table,from[i]);
	return to;
}