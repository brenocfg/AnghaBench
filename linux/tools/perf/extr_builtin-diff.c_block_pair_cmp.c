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
struct hist_entry {struct block_info* block_info; } ;
struct block_info {scalar_t__ start; scalar_t__ end; TYPE_1__* sym; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int block_pair_cmp(struct hist_entry *a, struct hist_entry *b)
{
	struct block_info *bi_a = a->block_info;
	struct block_info *bi_b = b->block_info;
	int cmp;

	if (!bi_a->sym || !bi_b->sym)
		return -1;

	cmp = strcmp(bi_a->sym->name, bi_b->sym->name);

	if ((!cmp) && (bi_a->start == bi_b->start) && (bi_a->end == bi_b->end))
		return 0;

	return -1;
}