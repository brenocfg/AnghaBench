#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct super_block {int dummy; } ;
struct adfs_sb_info {unsigned int s_map_size; int /*<<< orphan*/  s_map2blk; struct adfs_discmap* s_map; } ;
struct adfs_discmap {int dummy; } ;

/* Variables and functions */
 struct adfs_sb_info* ADFS_SB (struct super_block*) ; 
 scalar_t__ scan_free_map (struct adfs_sb_info*,int /*<<< orphan*/ ) ; 
 unsigned int signed_asl (unsigned int,int /*<<< orphan*/ ) ; 

unsigned int
adfs_map_free(struct super_block *sb)
{
	struct adfs_sb_info *asb = ADFS_SB(sb);
	struct adfs_discmap *dm;
	unsigned int total = 0;
	unsigned int zone;

	dm   = asb->s_map;
	zone = asb->s_map_size;

	do {
		total += scan_free_map(asb, dm++);
	} while (--zone > 0);

	return signed_asl(total, asb->s_map2blk);
}