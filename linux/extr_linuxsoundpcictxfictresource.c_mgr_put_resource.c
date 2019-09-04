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
struct rsc_mgr {unsigned int avail; int /*<<< orphan*/  rscs; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_resource (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

int mgr_put_resource(struct rsc_mgr *mgr, unsigned int n, unsigned int idx)
{
	put_resource(mgr->rscs, n, idx);
	mgr->avail += n;

	return 0;
}