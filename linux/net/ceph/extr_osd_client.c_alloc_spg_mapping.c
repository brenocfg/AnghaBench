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
struct ceph_spg_mapping {int /*<<< orphan*/  backoffs; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_ROOT ; 
 struct ceph_spg_mapping* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ceph_spg_mapping *alloc_spg_mapping(void)
{
	struct ceph_spg_mapping *spg;

	spg = kmalloc(sizeof(*spg), GFP_NOIO);
	if (!spg)
		return NULL;

	RB_CLEAR_NODE(&spg->node);
	spg->backoffs = RB_ROOT;
	return spg;
}