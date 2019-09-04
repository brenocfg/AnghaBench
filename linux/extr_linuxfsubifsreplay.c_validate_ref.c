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
struct ubifs_ref_node {int /*<<< orphan*/  jhead; int /*<<< orphan*/  offs; int /*<<< orphan*/  lnum; } ;
struct ubifs_info {unsigned int jhead_cnt; int leb_cnt; int main_first; unsigned int leb_size; int min_io_size; } ;
struct ubifs_bud {unsigned int jhead; unsigned int start; } ;

/* Variables and functions */
 int EINVAL ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*,int,unsigned int) ; 
 struct ubifs_bud* ubifs_search_bud (struct ubifs_info*,int) ; 

__attribute__((used)) static int validate_ref(struct ubifs_info *c, const struct ubifs_ref_node *ref)
{
	struct ubifs_bud *bud;
	int lnum = le32_to_cpu(ref->lnum);
	unsigned int offs = le32_to_cpu(ref->offs);
	unsigned int jhead = le32_to_cpu(ref->jhead);

	/*
	 * ref->offs may point to the end of LEB when the journal head points
	 * to the end of LEB and we write reference node for it during commit.
	 * So this is why we require 'offs > c->leb_size'.
	 */
	if (jhead >= c->jhead_cnt || lnum >= c->leb_cnt ||
	    lnum < c->main_first || offs > c->leb_size ||
	    offs & (c->min_io_size - 1))
		return -EINVAL;

	/* Make sure we have not already looked at this bud */
	bud = ubifs_search_bud(c, lnum);
	if (bud) {
		if (bud->jhead == jhead && bud->start <= offs)
			return 1;
		ubifs_err(c, "bud at LEB %d:%d was already referred", lnum, offs);
		return -EINVAL;
	}

	return 0;
}