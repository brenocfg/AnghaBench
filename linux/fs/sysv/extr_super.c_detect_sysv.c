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
typedef  int u32 ;
struct sysv_sb_info {int s_forced_ro; int /*<<< orphan*/  s_type; int /*<<< orphan*/  s_bytesex; struct super_block* s_sb; } ;
struct sysv4_super_block {int /*<<< orphan*/  s_time; int /*<<< orphan*/  s_nfree; int /*<<< orphan*/  s_type; int /*<<< orphan*/  s_magic; } ;
struct super_block {int /*<<< orphan*/  s_id; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  scalar_t__ __le32 ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int BLOCK_SIZE ; 
 int /*<<< orphan*/  BYTESEX_BE ; 
 int /*<<< orphan*/  BYTESEX_LE ; 
 int /*<<< orphan*/  FSTYPE_AFS ; 
 int /*<<< orphan*/  FSTYPE_SYSV2 ; 
 int /*<<< orphan*/  FSTYPE_SYSV4 ; 
 scalar_t__ JAN_1_1980 ; 
 scalar_t__ cpu_to_be32 (int) ; 
 scalar_t__ cpu_to_le32 (int) ; 
 int fs16_to_cpu (struct sysv_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ fs32_to_cpu (struct sysv_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_rdonly (struct super_block*) ; 

__attribute__((used)) static int detect_sysv(struct sysv_sb_info *sbi, struct buffer_head *bh)
{
	struct super_block *sb = sbi->s_sb;
	/* All relevant fields are at the same offsets in R2 and R4 */
	struct sysv4_super_block * sbd;
	u32 type;

	sbd = (struct sysv4_super_block *) (bh->b_data + BLOCK_SIZE/2);
	if (*(__le32 *)&sbd->s_magic == cpu_to_le32(0xfd187e20))
		sbi->s_bytesex = BYTESEX_LE;
	else if (*(__be32 *)&sbd->s_magic == cpu_to_be32(0xfd187e20))
		sbi->s_bytesex = BYTESEX_BE;
	else
		return 0;

	type = fs32_to_cpu(sbi, sbd->s_type);
 
 	if (fs16_to_cpu(sbi, sbd->s_nfree) == 0xffff) {
 		sbi->s_type = FSTYPE_AFS;
		sbi->s_forced_ro = 1;
 		if (!sb_rdonly(sb)) {
 			printk("SysV FS: SCO EAFS on %s detected, " 
 				"forcing read-only mode.\n", 
 				sb->s_id);
 		}
 		return type;
 	}
 
	if (fs32_to_cpu(sbi, sbd->s_time) < JAN_1_1980) {
		/* this is likely to happen on SystemV2 FS */
		if (type > 3 || type < 1)
			return 0;
		sbi->s_type = FSTYPE_SYSV2;
		return type;
	}
	if ((type > 3 || type < 1) && (type > 0x30 || type < 0x10))
		return 0;

	/* On Interactive Unix (ISC) Version 4.0/3.x s_type field = 0x10,
	   0x20 or 0x30 indicates that symbolic links and the 14-character
	   filename limit is gone. Due to lack of information about this
           feature read-only mode seems to be a reasonable approach... -KGB */

	if (type >= 0x10) {
		printk("SysV FS: can't handle long file names on %s, "
		       "forcing read-only mode.\n", sb->s_id);
		sbi->s_forced_ro = 1;
	}

	sbi->s_type = FSTYPE_SYSV4;
	return type >= 0x10 ? type >> 4 : type;
}