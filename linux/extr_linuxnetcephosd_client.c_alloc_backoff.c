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
struct ceph_osd_backoff {int /*<<< orphan*/  id_node; int /*<<< orphan*/  spg_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 struct ceph_osd_backoff* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ceph_osd_backoff *alloc_backoff(void)
{
	struct ceph_osd_backoff *backoff;

	backoff = kzalloc(sizeof(*backoff), GFP_NOIO);
	if (!backoff)
		return NULL;

	RB_CLEAR_NODE(&backoff->spg_node);
	RB_CLEAR_NODE(&backoff->id_node);
	return backoff;
}