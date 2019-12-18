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
typedef  scalar_t__ z_erofs_next_pcluster_t ;
struct z_erofs_pcluster {scalar_t__ next; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_BUGON (int) ; 
 size_t JQ_BYPASS ; 
 size_t JQ_SUBMIT ; 
 int /*<<< orphan*/  WRITE_ONCE (scalar_t__,scalar_t__*) ; 
 scalar_t__ Z_EROFS_PCLUSTER_TAIL ; 
 scalar_t__ Z_EROFS_PCLUSTER_TAIL_CLOSED ; 

__attribute__((used)) static void move_to_bypass_jobqueue(struct z_erofs_pcluster *pcl,
				    z_erofs_next_pcluster_t qtail[],
				    z_erofs_next_pcluster_t owned_head)
{
	z_erofs_next_pcluster_t *const submit_qtail = qtail[JQ_SUBMIT];
	z_erofs_next_pcluster_t *const bypass_qtail = qtail[JQ_BYPASS];

	DBG_BUGON(owned_head == Z_EROFS_PCLUSTER_TAIL_CLOSED);
	if (owned_head == Z_EROFS_PCLUSTER_TAIL)
		owned_head = Z_EROFS_PCLUSTER_TAIL_CLOSED;

	WRITE_ONCE(pcl->next, Z_EROFS_PCLUSTER_TAIL_CLOSED);

	WRITE_ONCE(*submit_qtail, owned_head);
	WRITE_ONCE(*bypass_qtail, &pcl->next);

	qtail[JQ_BYPASS] = &pcl->next;
}