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
struct TYPE_2__ {long long idx_growth; long long data_growth; long long dd_growth; } ;
struct ubifs_info {int /*<<< orphan*/  space_lock; TYPE_1__ bi; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long long get_liability(struct ubifs_info *c)
{
	long long liab;

	spin_lock(&c->space_lock);
	liab = c->bi.idx_growth + c->bi.data_growth + c->bi.dd_growth;
	spin_unlock(&c->space_lock);
	return liab;
}