#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_7__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sysv_zone_t ;
struct super_block {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct TYPE_9__ {int /*<<< orphan*/ * i_data; } ;
struct TYPE_8__ {int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ Indirect ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 TYPE_7__* SYSV_I (struct inode*) ; 
 int /*<<< orphan*/  SYSV_SB (struct super_block*) ; 
 int /*<<< orphan*/  add_chain (TYPE_1__*,struct buffer_head*,int /*<<< orphan*/ *) ; 
 int block_to_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 struct buffer_head* sb_bread (struct super_block*,int) ; 
 int /*<<< orphan*/  verify_chain (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static Indirect *get_branch(struct inode *inode,
			    int depth,
			    int offsets[],
			    Indirect chain[],
			    int *err)
{
	struct super_block *sb = inode->i_sb;
	Indirect *p = chain;
	struct buffer_head *bh;

	*err = 0;
	add_chain(chain, NULL, SYSV_I(inode)->i_data + *offsets);
	if (!p->key)
		goto no_block;
	while (--depth) {
		int block = block_to_cpu(SYSV_SB(sb), p->key);
		bh = sb_bread(sb, block);
		if (!bh)
			goto failure;
		if (!verify_chain(chain, p))
			goto changed;
		add_chain(++p, bh, (sysv_zone_t*)bh->b_data + *++offsets);
		if (!p->key)
			goto no_block;
	}
	return NULL;

changed:
	brelse(bh);
	*err = -EAGAIN;
	goto no_block;
failure:
	*err = -EIO;
no_block:
	return p;
}