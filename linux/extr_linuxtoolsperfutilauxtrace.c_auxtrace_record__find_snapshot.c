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
typedef  int /*<<< orphan*/  u64 ;
struct auxtrace_record {int (* find_snapshot ) (struct auxtrace_record*,int,struct auxtrace_mmap*,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct auxtrace_mmap {int dummy; } ;

/* Variables and functions */
 int stub1 (struct auxtrace_record*,int,struct auxtrace_mmap*,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int auxtrace_record__find_snapshot(struct auxtrace_record *itr, int idx,
				   struct auxtrace_mmap *mm,
				   unsigned char *data, u64 *head, u64 *old)
{
	if (itr && itr->find_snapshot)
		return itr->find_snapshot(itr, idx, mm, data, head, old);
	return 0;
}