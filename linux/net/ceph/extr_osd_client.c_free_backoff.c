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
struct ceph_osd_backoff {int /*<<< orphan*/  end; int /*<<< orphan*/  begin; int /*<<< orphan*/  id_node; int /*<<< orphan*/  spg_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_EMPTY_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  free_hoid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ceph_osd_backoff*) ; 

__attribute__((used)) static void free_backoff(struct ceph_osd_backoff *backoff)
{
	WARN_ON(!RB_EMPTY_NODE(&backoff->spg_node));
	WARN_ON(!RB_EMPTY_NODE(&backoff->id_node));

	free_hoid(backoff->begin);
	free_hoid(backoff->end);
	kfree(backoff);
}