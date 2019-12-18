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
 int /*<<< orphan*/  RB_EMPTY_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct ceph_spg_mapping*) ; 

__attribute__((used)) static void free_spg_mapping(struct ceph_spg_mapping *spg)
{
	WARN_ON(!RB_EMPTY_NODE(&spg->node));
	WARN_ON(!RB_EMPTY_ROOT(&spg->backoffs));

	kfree(spg);
}