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
struct xenvif {int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  RING_HAS_UNCONSUMED_REQUESTS (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool xenvif_ctrl_work_todo(struct xenvif *vif)
{
	if (likely(RING_HAS_UNCONSUMED_REQUESTS(&vif->ctrl)))
		return true;

	return false;
}