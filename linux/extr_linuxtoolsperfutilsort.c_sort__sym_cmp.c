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
struct TYPE_2__ {int /*<<< orphan*/  sym; } ;
struct hist_entry {TYPE_1__ ms; int /*<<< orphan*/  hists; int /*<<< orphan*/  ip; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ _sort__addr_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _sort__sym_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dso ; 
 scalar_t__ hists__has (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sort__dso_cmp (struct hist_entry*,struct hist_entry*) ; 

__attribute__((used)) static int64_t
sort__sym_cmp(struct hist_entry *left, struct hist_entry *right)
{
	int64_t ret;

	if (!left->ms.sym && !right->ms.sym)
		return _sort__addr_cmp(left->ip, right->ip);

	/*
	 * comparing symbol address alone is not enough since it's a
	 * relative address within a dso.
	 */
	if (!hists__has(left->hists, dso) || hists__has(right->hists, dso)) {
		ret = sort__dso_cmp(left, right);
		if (ret != 0)
			return ret;
	}

	return _sort__sym_cmp(left->ms.sym, right->ms.sym);
}