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
struct bman_portal {int /*<<< orphan*/  p; } ;

/* Variables and functions */
 int /*<<< orphan*/  bm_rcr_cce_prefetch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bm_rcr_cce_update (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void update_rcr_ci(struct bman_portal *p, int avail)
{
	if (avail)
		bm_rcr_cce_prefetch(&p->p);
	else
		bm_rcr_cce_update(&p->p);
}