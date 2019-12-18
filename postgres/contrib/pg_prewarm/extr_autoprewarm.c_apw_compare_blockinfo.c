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
typedef  int /*<<< orphan*/  BlockInfoRecord ;

/* Variables and functions */
 int /*<<< orphan*/  blocknum ; 
 int /*<<< orphan*/  cmp_member_elem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  database ; 
 int /*<<< orphan*/  filenode ; 
 int /*<<< orphan*/  forknum ; 
 int /*<<< orphan*/  tablespace ; 

__attribute__((used)) static int
apw_compare_blockinfo(const void *p, const void *q)
{
	const BlockInfoRecord *a = (const BlockInfoRecord *) p;
	const BlockInfoRecord *b = (const BlockInfoRecord *) q;

	cmp_member_elem(database);
	cmp_member_elem(tablespace);
	cmp_member_elem(filenode);
	cmp_member_elem(forknum);
	cmp_member_elem(blocknum);

	return 0;
}