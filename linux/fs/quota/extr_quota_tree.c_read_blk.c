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
typedef  int uint ;
struct super_block {TYPE_1__* s_op; } ;
struct qtree_mem_dqinfo {int dqi_blocksize_bits; int /*<<< orphan*/  dqi_usable_bs; int /*<<< orphan*/  dqi_type; struct super_block* dqi_sb; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* quota_read ) (struct super_block*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct super_block*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t read_blk(struct qtree_mem_dqinfo *info, uint blk, char *buf)
{
	struct super_block *sb = info->dqi_sb;

	memset(buf, 0, info->dqi_usable_bs);
	return sb->s_op->quota_read(sb, info->dqi_type, buf,
	       info->dqi_usable_bs, blk << info->dqi_blocksize_bits);
}