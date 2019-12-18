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
struct TYPE_2__ {scalar_t__ lsn; } ;
typedef  TYPE_1__ RewriteMappingFile ;
typedef  int /*<<< orphan*/  ListCell ;

/* Variables and functions */
 scalar_t__ lfirst (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
file_sort_by_lsn(const ListCell *a_p, const ListCell *b_p)
{
	RewriteMappingFile *a = (RewriteMappingFile *) lfirst(a_p);
	RewriteMappingFile *b = (RewriteMappingFile *) lfirst(b_p);

	if (a->lsn < b->lsn)
		return -1;
	else if (a->lsn > b->lsn)
		return 1;
	return 0;
}